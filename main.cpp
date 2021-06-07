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
  path_vector.push_back(std::string("/home/civ/CGPraktikum/data/bunny/bunny_scaled.ply"));
  path_vector.push_back(std::string("/home/civ/CGPraktikum/data/basicObjects/cube_scaled.ply"));
  // Erzeuge die Szene mit dem default Konstruktor und lade die Modelle
  auto scene = std::make_shared<Scene>();
  scene->load(path_vector);


  /* Aufgabenblatt 1: Instanziieren Sie einen WireframeRenderer */
  auto wireFrameRenderer = new WireframeRenderer(scene, img);


//  Color red = Color(0.7, 0.0, 0.0);
  Color green = Color(0.0, 0.7, 0.0);
// Color blue = Color(0.0, 0.0, 0.7);

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


  //Aufgabenblatt 2 Aufgabe 2 Test
  GLMatrix mTest = GLMatrix();
  //erster zeile
  mTest.setValue(0,0,3);
  mTest.setValue(0,1,4);
  mTest.setValue(0,2,7);
  //zweite zeile
  mTest.setValue(1,0,3);
  mTest.setValue(1,1,8);
  mTest.setValue(1,2,5);
  //dritte zeile
  mTest.setValue(2,0,2);
  mTest.setValue(2,1,6);
  mTest.setValue(2,2,4);
  //translation
  mTest.setValue(0,3,5);
  mTest.setValue(1,3,5);
  mTest.setValue(2,3,5);

  GLMatrix mTest2 = GLMatrix();
  //erster zeile
  mTest2.setValue(0,0,5);
  mTest2.setValue(0,1,8);
  mTest2.setValue(0,2,2);
  //zweite zeile
  mTest2.setValue(1,0,6);
  mTest2.setValue(1,1,3);
  mTest2.setValue(1,2,6);
  //dritte zeile
  mTest2.setValue(2,0,4);
  mTest2.setValue(2,1,7);
  mTest2.setValue(2,2,5);
  //translation
  mTest2.setValue(0,3,5);
  mTest2.setValue(1,3,5);
  mTest2.setValue(2,3,5);

  GLVector vTest = GLVector(2,4,6);
  GLPoint pTest = GLPoint(4,7,2);
  GLVector vRes1;
  GLVector vRes2;
  GLMatrix mRes;

  //sollte (69,73,57) ergeben
  vRes1 = mTest * vTest;

  //sollte(59,83,63) ergeben
  vRes2 = mTest * pTest;

  //(67 85 65 75
  // 83 83 79 85
  // 62 62 60 65
  //  0  0  0  1)
  mRes = mTest * mTest2;

  std::cout<<vRes1;
  std::cout<<vRes2;
  std::cout<<mRes;

  /* Aufgabenblatt 2, Aufgabe 1: Rufen Sie Ihre renderScene-Methode hier auf */

  //wireFrameRenderer->renderScene(green);



  /* Setup der Camera - Erst ab Aufgabenblatt 3 relevant. */
  // Diese Einstellungen beziehen sich auf den world space
  // Beachten Sie, dass Sie in diesem Praktikum keine explizite Umwandlung in
  // den ViewSpace benötigen, da die Strahen für Raycasting und Raytracing im
  // World space definiert sind. Modelle müssen also lediglich in den World
  // space überführt werden
  
  /* Aufgabenblatt 3:  kommentieren Sie die Zeilen wieder ein, die eine Kamera erzeugen und zur Scene hinzufügen*/
  
  //  auto cam = std::make_shared<Camera>();
  //GLPoint eye = GLPoint(0.0, 0.0, 300.0);
  //cam->setEyePoint(eye);
  //cam->setUp(GLVector(0.0, 1.0, 0.0));
  //GLVector viewDirection = GLVector(0.0, 0, -1.0);
  //viewDirection.normalize();
  //cam->setViewDirection(viewDirection);
  //cam->setSize(img->getWidth(), img->getHeight());
  //scene->setCamera(cam);


  /* Aufgabenblatt 3: Erzeugen Sie mindestens eine Kugel und fügen Sie diese zur Szene hinzu*/
    
  /* Aufgabenblatt 4: Setzen Sie materialeigenschaften für die Kugelen und die Modelle. Die Materialeigenschaften für eine Darstellung entsprechend der Beispiellösung ist in der Aufgabenstellung gegeben. */

  /* Aufgabenblatt 3: (Wenn nötig) Transformationen der Modelle im World space, sodass sie von der Kamera gesehen werden könnnen. Die nötigen Transformationen für eine Darstellung entsprechend der Beispiellösung ist in der Aufgabenstellung gegeben. */

  /* Stelle materialeigenschaften zur verfügung (Relevant für Aufgabenblatt 4)*/

  /* Aufgabenblatt 4  Fügen Sie ein Licht zur Szene hinzu */
  
    
  /* Aufgabenblatt 3: erzeugen Sie einen SolidRenderer (vorzugsweise mir einem shared_ptr) und rufen sie die Funktion renderRaycast auf */
  
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
