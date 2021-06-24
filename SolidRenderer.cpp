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
}
