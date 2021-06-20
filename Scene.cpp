#include "Scene.hpp"

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

Scene::Scene() {}


/**
 * Gibt zurück ob ein gegebener Strahl ein Objekt (Modell oder Kugel) der Szene trifft
 *  (Aufgabenblatt 3)
 */
bool Scene::intersect(const Ray &ray, HitRecord &hitRecord,
                      const float epsilon) {
    //Variable, um den Return Wert zu speichern
    bool hit = false;
    int sphereId = 0;
    int triangleId = 0;
    int modelId = 0;
    //Alle Spheren der Scene checken
    for(Sphere sphere : mSpheres){
        if(sphereIntersect(ray, sphere, hitRecord, epsilon)){
            //HitRecord aktualisieren           
            hitRecord.color = sphere.getMaterial().color;
            hitRecord.sphereId = sphereId;
            hit = true;
        }
        sphereId++;
    }
    //Alle Dreiecke der Scene checken
    for (Model model : mModels) {
        modelId++;
        for (Triangle triangle : model.mTriangles){
            //Dreieck an Tranformation anpassen
            Triangle transformedTriangle = Triangle();
            transformedTriangle.vertex[0] = model.getTransformation() * triangle.vertex[0];
            transformedTriangle.vertex[1] = model.getTransformation() * triangle.vertex[1];
            transformedTriangle.vertex[2] = model.getTransformation() * triangle.vertex[2];
            transformedTriangle.normal = crossProduct(transformedTriangle.vertex[0] - transformedTriangle.vertex[2], transformedTriangle.vertex[1] - transformedTriangle.vertex[2]);
            triangleId++;
             if(triangleIntersect(ray, transformedTriangle, hitRecord, epsilon)){
                 //HitRecord aktualisieren
                 hitRecord.color = model.getMaterial().color;
                 hitRecord.triangleId = triangleId;
                 hitRecord.modelId = modelId;
                 hit = true;
             }
        }}

    return hit;
}

/** Aufgabenblatt 3: Gibt zurück ob ein gegebener Strahl ein Dreieck  eines Modells der Szene trifft
 *  Diese Methode sollte in Scene::intersect für jedes Objektdreieck aufgerufen werden
 *  Aufgabenblatt 4: Diese Methode befüllt den den HitRecord im Fall eines Treffers mit allen für das shading notwendigen informationen
 */
bool Scene::triangleIntersect(const Ray &ray, const Triangle &triangle,
                              HitRecord &hitRecord, const float epsilon) {
    if (dotProduct(ray.direction, triangle.normal) == 0) {
        return false; // Strahl verläuft parallel zum Dreieck
    }

    // Berechnung des Strahlparameters
    double t = dotProduct((triangle.vertex[2] - ray.origin), triangle.normal) / dotProduct(ray.direction, triangle.normal);

    // Berechnung des Schnittpunkts
    GLPoint intersection = ray.origin + t * ray.direction;

    // Prüfen, ob der Schnittpunkt innerhalb des Dreiecks liegt
    double triangleArea = crossProduct(triangle.vertex[0] - triangle.vertex[2], triangle.vertex[1] - triangle.vertex[2]).norm() / 2.0;

    double subtriangleArea1 = crossProduct(triangle.vertex[0] - intersection, triangle.vertex[1] - intersection).norm() / 2.0;
    double subtriangleArea2 = crossProduct(triangle.vertex[0] - intersection, triangle.vertex[2] - intersection).norm() / 2.0;
    double subtriangleArea3 = crossProduct(triangle.vertex[1] - intersection, triangle.vertex[2] - intersection).norm() / 2.0;

    if (triangleArea + epsilon < subtriangleArea1 + subtriangleArea2 + subtriangleArea3) {
        return false; // Schnittpunkt liegt außerhalb des Dreiecks
    }

    double parameter = (intersection - ray.origin).norm();

    if (hitRecord.parameter > 0.0 && parameter > hitRecord.parameter) {
        return false; // Schnittpunkt ist zu weit entfernt
    }

    hitRecord.parameter = parameter;
    hitRecord.intersectionPoint = intersection;

    return true;
}

/** Aufgabenblatt 3: Gibt zurück ob ein gegebener Strahl eine Kugel der Szene trifft
 *  Diese Methode sollte in Scene::intersect für jede Kugel aufgerufen werden
 *  Aufgabenblatt 4: Diese Methode befüllt den den HitRecord im Fall eines Treffers mit allen für das shading notwendigen informationen
*/
bool Scene::sphereIntersect(const Ray &ray, const Sphere &sphere,
                            HitRecord &hitRecord, const float epsilon) {
    //Variablen setzen
        GLPoint e = ray.origin;
        GLVector v = ray.direction;
        double t0, t1;
        GLPoint m = sphere.getPosition();
        double r = sphere.getRadius();
        GLVector d = e - m;

        //a,b,c für quadratische Formel setzen (für ax² + bx + c)
        double a = dotProduct(v,v);
        double b = 2 * dotProduct(v, d);
        double c = dotProduct(d, d) - r*r;

        //Quadratische Formel lösen
        double discr = b * b - 4 * a * c;
        if (discr < 0){
            return false;
        }
        else if (discr == 0){
            t0 = t1 = - 0.5 * b / a;
        }
          else {
            double q = (b > 0) ?
                -0.5 * (b + sqrt(discr)) :
                -0.5 * (b - sqrt(discr));
            t0 = q / a;
            t1 = c / q;
        }

        //Überprüfe welches t näher an dem Augpunkt liegt
        if (t0 > t1) std::swap(t0, t1);
        if (t0 < 0) {
            t0 = t1;
            if (t0 < 0){
                return false;
            }
        }

        //Variablen für HitRecord setzen
        double parameter = (t0 * v).norm();
        GLPoint intersectionPoint = e + t0 * v;


        //Überprüfe, ob neuer Parameter näher am Augpunkt liegt als der Alte, falls ja, aktualisiere HitRecord
        if (hitRecord.parameter > 0.0 && hitRecord.parameter < parameter) {
            return false;
        }

        hitRecord.parameter = parameter;
        hitRecord.intersectionPoint = intersectionPoint;
        return true;
}

/**
** Liest die Modelle (deren Dateinamen in pFiles stehen) ein und speichert sie
*in mModels
**/
void Scene::load(const std::vector<std::string> &pFiles) {
  std::cout << "Laden der PLY Dateien:" << std::endl;
  // Für alle Objekte (Objekt meint hier das selbe wie Model)
  for (int obj_nr = 0; obj_nr < pFiles.size(); obj_nr++) {
    std::cout << "\tModel-Index: " << obj_nr << std::endl;
    // Assimp übernimmt das Einlesen der ply-Dateien
    Assimp::Importer importer;
    const aiScene *assimpScene = importer.ReadFile(
        pFiles[obj_nr], aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                            aiProcess_JoinIdenticalVertices |
                            aiProcess_SortByPType);
    assert(assimpScene);
    auto meshes = assimpScene->mMeshes;
    // Neues Model erstellen
    Model model = Model();

    // Für alle Meshes des Models
    for (int i = 0; i < assimpScene->mNumMeshes; i++) {
      std::cout << "\t\tMesh-Index: " << i << " (" << meshes[i]->mNumFaces
                << " Faces)" << std::endl;
      auto faces = meshes[i]->mFaces;
      auto vertices = meshes[i]->mVertices;

      // Für alle Faces einzelner Meshes
      for (int j = 0; j < meshes[i]->mNumFaces; j++) {
        // Dreieck konstruieren und nötige Werte berechnen
        Triangle tri;
        assert(faces[j].mNumIndices == 3);
        tri.vertex[0] = GLPoint(vertices[faces[j].mIndices[0]].x,
                                vertices[faces[j].mIndices[0]].y,
                                vertices[faces[j].mIndices[0]].z);
        tri.vertex[1] = GLPoint(vertices[faces[j].mIndices[1]].x,
                                vertices[faces[j].mIndices[1]].y,
                                vertices[faces[j].mIndices[1]].z);
        tri.vertex[2] = GLPoint(vertices[faces[j].mIndices[2]].x,
                                vertices[faces[j].mIndices[2]].y,
                                vertices[faces[j].mIndices[2]].z);
        GLVector normal = crossProduct(tri.vertex[1] - tri.vertex[0],
                                       tri.vertex[2] - tri.vertex[0]);
        normal.normalize();
        tri.normal = normal;
        // Jedes Dreieck zum Vector der Dreiecke des aktuellen Models hinzufügen
        model.mTriangles.push_back(tri);
      }
    }
    // Immer das gleiche Material für das Model setzen
    Material material;
    material.color = Color(0.00, 1.00, 0.00);
    model.setMaterial(material);
    // Jedes Model zum Vector der Models der Scene hinzufügen
    mModels.push_back(model);
  }

  std::cout << "Laden der PLY Dateien abgeschlossen." << std::endl;
}

void Scene::setCamera(std::shared_ptr<Camera> cam) { mCamera = cam; }

std::shared_ptr<Camera> Scene::getCamera() const { return mCamera; }

GLPoint Scene::getViewPoint() const {
  if (mCamera)
    return mCamera->getEyePoint();
  else {
    std::cerr << "No Camera set to get view point from." << std::endl;
    return GLPoint(0, 0, 0);
  }
}



void Scene::addPointLight(GLPoint pointLight) {
  mPointLights.push_back(pointLight);
}

void Scene::addModel(Model model) { mModels.push_back(model); }

void Scene::addSphere(Sphere sphere) { mSpheres.push_back(sphere); }

std::vector<Model> &Scene::getModels() { return mModels; }

std::vector<Sphere> &Scene::getSpheres() { return mSpheres; }

std::vector<GLPoint> &Scene::getPointLights() { return mPointLights; }
