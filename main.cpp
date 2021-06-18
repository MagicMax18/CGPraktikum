#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <unistd.h>

#include <algorithm>
#include <assimp/Importer.hpp>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Scene.hpp"
#include "SolidRenderer.hpp"
#include "WireframeRenderer.hpp"
#include "math.hpp"

int main(int argc, char **argv) {
  // Dimensionen des Ergebnisbildes im Konstruktor setzen
  std::shared_ptr<Image> img = std::make_shared<Image>(401, 301);

  // Verwendete Modelle festlegen
  std::vector<std::string> path_vector;
  path_vector.push_back(std::string("/home/osboxes/CGPraktikum/data/bunny/bunny_scaled.ply"));
  path_vector.push_back(std::string("/home/osboxes/CGPraktikum/data/basicObjects/cube_scaled.ply"));
  // Erzeuge die Szene mit dem default Konstruktor und lade die Modelle
  auto scene = std::make_shared<Scene>();
  scene->load(path_vector);


  /* Aufgabenblatt 1: Instanziieren Sie einen WireframeRenderer */
//  auto wireFrameRenderer = new WireframeRenderer(scene, img);


//  Color red = Color(0.7, 0.0, 0.0);
//  Color green = Color(0.0, 0.7, 0.0);
//  Color blue = Color(0.0, 0.0, 0.7);

  /* Aufgabenblatt 1, Aufgabe 2: Testen Sie Ihre drawBresenhamLine-Methode hier */
//  GLPoint startPunkt = GLPoint(200, 150, 0);

//  GLPoint testPunkt1 = GLPoint(100, 170, 0);
//  GLPoint testPunkt2 = GLPoint(180, 250, 0);
//  GLPoint testPunkt3 = GLPoint(220, 250, 0);
//  GLPoint testPunkt4 = GLPoint(300, 170, 0);
//  GLPoint testPunkt5 = GLPoint(300, 130, 0);
//  GLPoint testPunkt6 = GLPoint(220, 50, 0);
//  GLPoint testPunkt7 = GLPoint(180, 50, 0);
//  GLPoint testPunkt8 = GLPoint(100, 130, 0);

//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt4, red); // Oktant 1
//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt3, red); // Oktant 2

//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt2, red); // Oktant 3
//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt1, red); // Oktant 4

//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt8, red); // Oktant 5
//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt7, red); // Oktant 6

//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt6, red); // Oktant 7
//  wireFrameRenderer->drawBresenhamLine(startPunkt, testPunkt5, red); // Oktant 8

  /* Aufgabenblatt 1, Aufgabe 3: Testen Sie Ihre seedFillArea-Methode hier */

  // großes Dreieck zeichnen
//  GLPoint a = GLPoint(100, 100, 0);
//  GLPoint b = GLPoint(300, 100, 0);
//  GLPoint c = GLPoint(300, 200, 0);

//  wireFrameRenderer->drawBresenhamLine(a, b, red);
//  wireFrameRenderer->drawBresenhamLine(a, c, red);
//  wireFrameRenderer->drawBresenhamLine(b, c, red);


//  // kleines Dreieck zeichnen
//  GLPoint d = GLPoint(130, 110, 0);
//  GLPoint e = GLPoint(290, 110, 0);
//  GLPoint f = GLPoint(290, 190, 0);

//  wireFrameRenderer->drawBresenhamLine(d, e, red);
//  wireFrameRenderer->drawBresenhamLine(d, f, red);
//  wireFrameRenderer->drawBresenhamLine(e, f, red);


    //GLPoint seed = GLPoint(200, 120, 0); // Seed für Fläche ohne Loch
//    GLPoint seed = GLPoint(120, 105, 0); // Seed für Fläche mit Loch

//  wireFrameRenderer->seedFillArea(seed, red, green);

  /* Aufgabenblatt 2, Aufgabe 3: Setzen Sie die Transformationen der Modelle */
//   wireFrameRenderer->mScene->getModels()[0].setTranslation(GLVector(250, 100, 0));
//   wireFrameRenderer->mScene->getModels()[0].setScale(GLVector(0.8, 0.8, 0.8));
//   wireFrameRenderer->mScene->getModels()[0].setRotation(GLVector(0.0, AI_MATH_PI * 5.0 / 180.0, 0.0));

//   wireFrameRenderer->mScene->getModels()[1].setTranslation(GLVector(100, 100, 0));
//   wireFrameRenderer->mScene->getModels()[1].setScale(GLVector(0.9, 0.9, 0.9));
//   wireFrameRenderer->mScene->getModels()[1].setRotation(GLVector(AI_MATH_PI * 20.0 / 180.0, AI_MATH_PI * 45.0 / 180.0, 0.0));


  /* Aufgabenblatt 2, Aufgabe 1: Rufen Sie Ihre renderScene-Methode hier auf */
//  wireFrameRenderer->renderScene(green);


  /* Setup der Camera - Erst ab Aufgabenblatt 3 relevant. */
  // Diese Einstellungen beziehen sich auf den world space
  // Beachten Sie, dass Sie in diesem Praktikum keine explizite Umwandlung in
  // den ViewSpace benötigen, da die Strahen für Raycasting und Raytracing im
  // World space definiert sind. Modelle müssen also lediglich in den World
  // space überführt werden
  
  /* Aufgabenblatt 3:  kommentieren Sie die Zeilen wieder ein, die eine Kamera erzeugen und zur Scene hinzufügen*/
  
    auto cam = std::make_shared<Camera>();
  GLPoint eye = GLPoint(0.0, 0.0, 300.0);
  cam->setEyePoint(eye);
  cam->setUp(GLVector(0.0, 1.0, 0.0));
  GLVector viewDirection = GLVector(0.0, 0, -1.0);
  viewDirection.normalize();
  cam->setViewDirection(viewDirection);
  cam->setSize(img->getWidth(), img->getHeight());
  scene->setCamera(cam);


  /* Aufgabenblatt 3: Erzeugen Sie mindestens eine Kugel und fügen Sie diese zur Szene hinzu*/
  const double sphereRadius = 50.0;
  Sphere leftSphere = Sphere(GLPoint(-150.0, 0.0, -30.0), sphereRadius);
  scene->addSphere(leftSphere);
  Sphere rightSphere = Sphere(GLPoint(150.0, 0.0, -30.0), sphereRadius);
  scene->addSphere(rightSphere);
    
  /* Aufgabenblatt 4: Setzen Sie materialeigenschaften für die Kugelen und die Modelle. Die Materialeigenschaften für eine Darstellung entsprechend der Beispiellösung ist in der Aufgabenstellung gegeben. */

  /* Aufgabenblatt 3: (Wenn nötig) Transformationen der Modelle im World space, sodass sie von der Kamera gesehen werden könnnen. Die nötigen Transformationen für eine Darstellung entsprechend der Beispiellösung ist in der Aufgabenstellung gegeben. */
  //bunny
  scene->getModels()[0].setTranslation(GLVector(0.0, -10.0, -30.0));
  scene->getModels()[0].setRotation(GLVector(0.0, AI_MATH_PI * 170.0 / 180.0, 0.0));

  //cube
  scene->getModels()[1].setTranslation(GLVector(0.0, -100.0, 0.0));


  /* Stelle materialeigenschaften zur verfügung (Relevant für Aufgabenblatt 4)*/

  /* Aufgabenblatt 4  Fügen Sie ein Licht zur Szene hinzu */
  
    
  /* Aufgabenblatt 3: erzeugen Sie einen SolidRenderer (vorzugsweise mir einem shared_ptr) und rufen sie die Funktion renderRaycast auf */
  SolidRenderer solidRenderer = SolidRenderer(scene, img, cam);
  solidRenderer.renderRaycast();
  
  // Schreiben des Bildes in Datei
  if (argc > 1) {
    img->writeAsPPM(argv[1]);
    std::cout << "Bild mit Dimensionen " << img->getWidth() << "x"
              << img->getHeight() << " in Datei " << argv[1] << " geschrieben."
              << std::endl;
  } else {
    std::cerr
        << "Fehler: Kein Dateiname angegeben. Es wurde kein Output generiert."
        << std::endl;
  }

  return 0;
}
