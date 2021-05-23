#pragma once

#include "Image.hpp"
#include "Model.hpp"
#include "Scene.hpp"

class WireframeRenderer {
 public:
  // construct WireframeRenderer. Pointers mImage, mScene are are constructed by
  // passing the pointers image, scene. (pointers image and scene are ivalidated
  // )
  WireframeRenderer(std::shared_ptr<Scene> scene, std::shared_ptr<Image> image)
      : mImage(image), mScene(scene) {}

  void renderScene(Color color);

  void drawBresenhamLine(GLPoint p1, GLPoint p2, Color color);

  void seedFillArea(GLPoint seed, Color borderColor, Color fillColor);

  std::shared_ptr<Image> mImage;
  std::shared_ptr<Scene> mScene;

private:

  void drawBresenhamLineOct1(GLPoint p1, GLPoint p2, Color color);
  void drawBresenhamLineOct2(GLPoint p1, GLPoint p2, Color color);
  void drawBresenhamLineOct3(GLPoint p1, GLPoint p2, Color color);
  void drawBresenhamLineOct4(GLPoint p1, GLPoint p2, Color color);
  void drawBresenhamLineOct5(GLPoint p1, GLPoint p2, Color color);
  void drawBresenhamLineOct6(GLPoint p1, GLPoint p2, Color color);
  void drawBresenhamLineOct7(GLPoint p1, GLPoint p2, Color color);
  void drawBresenhamLineOct8(GLPoint p1, GLPoint p2, Color color);

};
