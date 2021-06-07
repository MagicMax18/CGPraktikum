
#include "Model.hpp"

// Konstruktor
Model::Model() {
  /* Aufgabenblatt 2, Aufgabe 3: Setzen Sie die default Werte */
    mRotation = GLVector(0,0,0);
    mTranslation = GLVector(0,0,0);
    mScale = GLVector(1,1,1);

}

// Setter für das Material
void Model::setMaterial(Material material) {
  mMaterial = Material();
  mMaterial.smooth = material.smooth;
  mMaterial.reflection = material.reflection;
  mMaterial.refraction = material.refraction;
  mMaterial.transparency = material.transparency;
  mMaterial.color = Color(material.color.r, material.color.g, material.color.b);
}

/* Aufgabenblatt 2, Aufgabe 3: Implementieren Sie die vier Methoden für die Transformationen hier */
void Model::setRotation(GLVector rotation){
    this->mRotation = rotation;
}
void Model::setTranslation(GLVector translation){
    this->mTranslation = translation;
}
void Model::setScale(GLVector scale){
    this->mScale = scale;
}

void Model::updateMatrix(){
    //Translation setzen
    mMatrix.setValue(0,3,mTranslation(0));
    mMatrix.setValue(1,3,mTranslation(1));
    mMatrix.setValue(2,3,mTranslation(2));

    //Skalierung setzen
    mMatrix.setValue(0,0,mScale(0));
    mMatrix.setValue(1,1,mScale(1));
    mMatrix.setValue(2,2,mScale(2));
}

GLMatrix Model::getTransformation() const { return mMatrix; }

Material Model::getMaterial() const { return mMaterial; }
