#include "SolidRenderer.hpp"

//#include <tbb/tbb.h>  // Include, nur wenn TBB genutzt werden soll

#define EPSILON \
  (1e-12)  // Epsilon um ungenauigkeiten und Rundungsfehler zu kompensieren

/**
 ** Erstellt mittels Raycast das Rendering der mScene in das mImage
 ** Precondition: Sowohl mImage, mScene, mCamera müssen gesetzt sein.
 **/
void SolidRenderer::renderRaycast() {
  // This function is part of the base
    if (mImage == NULL || mScene == NULL || mCamera == NULL) {
        return;
    }

  std::cout << "Rendern mittels Raycast gestartet." << std::endl;
  // Berechnung der einzelnen Rows in eigener Methode um die
  // Parallelisierbarkeit zu verbessern

  // Ohne parallelisierung:
    
//  for(size_t i = 0; i < mImage->getHeight(); ++i ){
//          computeImageRow( i );
//   }

  //  Parallelisierung mit OpenMP:
    
  #pragma omp parallel for
  for(size_t i = 0; i < mImage->getHeight(); ++i )
  {
      computeImageRow( i );
  }

  // Parallelisierung mit TBB:
    
  //tbb::parallel_for(size_t(0), mImage->getHeight(),
  //                /* lambda funktion*/ [&](size_t i) { computeImageRow(i); });
}

/**
 * Aufgabenblatt 3: Hier wird das Raycasting implementiert. Siehe Aufgabenstellung!
 * Precondition: Sowohl mImage, mScene und mCamera  müssen gesetzt sein.
 */
void SolidRenderer::computeImageRow(size_t rowNumber) {
    if (mImage == NULL || mScene == NULL || mCamera == NULL) {
        return;
    }

    Color inititalColor = Color(0.0, 0.0, 0.0);
    Color backgroundColor = Color(0.0, 0.0, 0.7); // blau

    for (unsigned int columnNumber = 0; columnNumber < mImage->getWidth(); ++columnNumber) {
        // Strahl zu dem Punkt erzeugen
        Ray ray = mCamera->getRay(columnNumber, rowNumber);

        // HitRecord für den Punkt aufbauen
        HitRecord hitRecord;

        // HitRecord initialisieren
        hitRecord.color = inititalColor;
        hitRecord.parameter = std::numeric_limits<double>::max();
        hitRecord.modelId = -1;
        hitRecord.triangleId = -1;
        hitRecord.sphereId = -1;
        hitRecord.recursions = 0;

        if (mScene->intersect(ray, hitRecord, 0.1)) {
            shade(hitRecord);
            mImage->setValue(columnNumber, rowNumber, hitRecord.color);
        }
        else
            mImage->setValue(columnNumber, rowNumber, backgroundColor);

    }
}

/**
 *  Aufgabenblatt 4: Hier wird das raytracing implementiert. Siehe Aufgabenstellung!
 */
void SolidRenderer::shade(HitRecord &r) {

    const unsigned int maxRecursions = 5;

    // Vektor vom Schnittpunkt zur Lichtquelle
    GLVector lightVector = mScene->getPointLights()[0] - r.intersectionPoint;
    lightVector.normalize(); 

    GLVector reflectionVector = r.normal * dotProduct(r.normal, lightVector) + crossProduct(crossProduct(r.normal, lightVector), r.normal) * -1;
    reflectionVector.normalize();

    const double kAmbient = 0.4;
    const double kDiffuse = 0.4;
    const double kSpecular = 0.2;
    const double potency = 10.0;


    // Prüfen, ob ein Hit erfolgte
    if (r.modelId == -1 && r.sphereId == -1) {
        return;
    }

    if (r.modelId != -1) {
        if (r.modelId > mScene->getModels().size()) {
            return; // modelId ist zu groß
        }
        r.color = mScene->getModels()[r.modelId].getMaterial().color;
    } else if (r.sphereId != -1) {
        if (r.sphereId > mScene->getSpheres().size()) {
            return; // sphereId ist zu groß
        }
        r.color = mScene->getSpheres()[r.sphereId].getMaterial().color;
    }

    // Das Umgebungslicht und die Lichtuelle senden weißes Licht mit voller Intensität aus
    // Dementsprechend sind die Werte von I_i und I_s gleich 1 und müssen nicht beachtet werden
    double lightIntensity = kSpecular * ::std::pow( dotProduct(reflectionVector, r.rayDirection), potency)
                            + kDiffuse * dotProduct(lightVector, r.normal)
                            + kAmbient;

    // Rundungsfehler beheben
    if (lightIntensity > 1.0)
        lightIntensity = 1.0;
    if (lightIntensity < 0.0)
        lightIntensity = 0.0;

    // Da die Lichtquelle weißes Licht emittiert, müssen alle Farbanteile in gleichem Maß angepasst werden
    r.color *= lightIntensity;

    // Schattenberechnung
    Ray shadeRay = Ray();
    shadeRay.direction = mScene->getPointLights()[0] - r.intersectionPoint;
    shadeRay.direction.normalize();
    // Ursprung des Schattenstrahls etwas in Richtung Lichtquelle verschieben, damit sich Objekte nicht selbst schneiden
    shadeRay.origin = r.intersectionPoint + shadeRay.direction * 0.1;

    HitRecord shadeRecord = HitRecord();
    shadeRecord.color = r.color;
    shadeRecord.parameter = (mScene->getPointLights()[0] - r.intersectionPoint).norm();
    shadeRecord.modelId = -1;
    shadeRecord.triangleId = -1;
    shadeRecord.sphereId = -1;
    shadeRecord.recursions = 0;

    if (mScene->intersect(shadeRay, shadeRecord, 0.01)) {
        // Der Schnittpunkt liegt im Schatten. Dementsprechend muss die Farbintensität reduziert werden
        r.color *= 0.4;
    }


    // Reflexion berechnen
    double reflection = 0.0;
    if (r.modelId != -1) {
        reflection = mScene->getModels()[r.modelId].getMaterial().reflection;
    } else {
        reflection = mScene->getSpheres()[r.sphereId].getMaterial().reflection;
    }

    if (reflection == 0.0 || maxRecursions == r.recursions) {
        // Nichtreflektierendes Material getroffen oder maximale Rekursionstiefe erreicht => Abbruch
        return;
    }

    // Bei perfekter Reflexion muss der HitRecord
    if (reflection == 1.0) {
        r.color = Color(0.0, 0.0, 0.0);
    }

    Ray reflectionRay = Ray();
    reflectionRay.direction = r.normal * dotProduct(r.normal, -1 * r.rayDirection) + crossProduct(crossProduct(r.normal, -1 * r.rayDirection), r.normal) * -1;
    reflectionRay.direction.normalize();
    // Ursprung des Reflexionsstrahls etwas in Strahlrichtung verschieben, damit sich Objekte nicht selbst schneiden
    reflectionRay.origin = r.intersectionPoint + reflectionRay.direction * 0.01;

    r.modelId = -1;
    r.triangleId = -1;
    r.sphereId = -1;
    r.parameter = std::numeric_limits<double>::max();
    r.recursions++;

    if (mScene->intersect(reflectionRay, r, 0.01)) {
        shade(r);
    }

}
