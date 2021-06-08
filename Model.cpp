
#include "Model.hpp"

// Konstruktor
Model::Model() {
  /* Aufgabenblatt 2, Aufgabe 3: Setzen Sie die default Werte */
    mRotation = GLVector(0, 0, 0);
    mTranslation = GLVector(0, 0, 0);
    mScale = GLVector(1, 1, 1);
    mMatrix = GLMatrix();
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
    this->mRotation = GLVector(rotation(0), rotation(1), rotation(2));

//    this->mRotation = this->mRotation + rotation;

    this->updateMatrix();
}
void Model::setTranslation(GLVector translation){
    this->mTranslation = GLVector(translation(0), translation(1), translation(2));

//    this->mTranslation = this->mTranslation + translation;

    this->updateMatrix();
}
void Model::setScale(GLVector scale){
    this->mScale = GLVector(scale(0), scale(1), scale(2));

//    this->mScale = GLVector(this->mScale(0) * scale(0), this->mScale(1) * scale(1), this->mScale(2) * scale(2));

    this->updateMatrix();
}

void Model::updateMatrix(){
    mMatrix = GLMatrix();

    //Translation setzen
    GLMatrix translationMatrix = GLMatrix();

    //Translationswerte entsprechen letzem Spaltenvektor
    translationMatrix.setValue(0, 3, mTranslation(0));
    translationMatrix.setValue(1, 3, mTranslation(1));
    translationMatrix.setValue(2, 3, mTranslation(2));

    //Skalierung setzen
    GLMatrix scaleMatrix = GLMatrix();

    //Skalenwerte entsprechen den Diagonal-Einträgen der Matrix
    scaleMatrix.setValue(0, 0, mScale(0));
    scaleMatrix.setValue(1, 1, mScale(1));
    scaleMatrix.setValue(2, 2, mScale(2));

    //Rotationsmatrix setzen

//    GLMatrix rotationMatrix = GLMatrix();

//    rotationMatrix.setValue(0, 0, std::cos(mRotation(1)) * std::cos(mRotation(2)));
//    rotationMatrix.setValue(0, 1, -std::cos(mRotation(1)) * std::sin(mRotation(2)));
//    rotationMatrix.setValue(0, 2, -std::sin(mRotation(1)));
//    rotationMatrix.setValue(1, 0, -std::sin(mRotation(0)) * std::sin(mRotation(1)) * std::cos(mRotation(2)) + std::cos(mRotation(0)) * std::sin(mRotation(2)));
//    rotationMatrix.setValue(1, 1, std::sin(mRotation(0)) * std::sin(mRotation(1)) * std::sin(mRotation(2)) + std::cos(mRotation(0)) * std::cos(mRotation(2)));
//    rotationMatrix.setValue(1, 2, -std::sin(mRotation(0)) * std::cos(mRotation(1)));
//    rotationMatrix.setValue(2, 0, std::cos(mRotation(0)) * std::sin(mRotation(1)) * std::cos(mRotation(2)) + std::sin(mRotation(0)) * std::sin(mRotation(2)));
//    rotationMatrix.setValue(2, 1, -std::cos(mRotation(0)) * std::sin(mRotation(1)) * std::sin(mRotation(2)) + std::sin(mRotation(0)) * std::cos(mRotation(2)));
//    rotationMatrix.setValue(2, 2, std::cos(mRotation(0)) * std::cos(mRotation(1)));

    GLMatrix xRotationMatrix = GLMatrix();
    GLMatrix yRotationMatrix = GLMatrix();
    GLMatrix zRotationMatrix = GLMatrix();

    //Drehmatrix für Rotation um x-Achse
    xRotationMatrix.setValue(1, 1, std::cos(mRotation(0)));
    xRotationMatrix.setValue(1, 2, - std::sin(mRotation(0)));
    xRotationMatrix.setValue(2, 1, std::sin(mRotation(0)));
    xRotationMatrix.setValue(2, 2, std::cos(mRotation(0)));

    //Drehmatrix für Rotation um y-Achse
    yRotationMatrix.setValue(0, 0, std::cos(mRotation(1)));
    yRotationMatrix.setValue(0, 2, std::sin(mRotation(1)));
    yRotationMatrix.setValue(2, 0, - std::sin(mRotation(1)));
    yRotationMatrix.setValue(2, 2, std::cos(mRotation(1)));

    //Drehmatrix für Rotation um z-Achse
    zRotationMatrix.setValue(0, 0, std::cos(mRotation(2)));
    zRotationMatrix.setValue(0, 1, - std::sin(mRotation(2)));
    zRotationMatrix.setValue(1, 0, std::sin(mRotation(2)));
    zRotationMatrix.setValue(1, 1, std::cos(mRotation(2)));

    //zuerst anhand von (0, 0, 0) skalieren
    mMatrix = scaleMatrix * mMatrix;

    //danach die Rotationen um die Koordinatenachsen ausführen, beginnend bei der x-Achse
    mMatrix = xRotationMatrix * mMatrix;
    mMatrix = yRotationMatrix * mMatrix;
    mMatrix = zRotationMatrix * mMatrix;

    //abschließend die Translation ausführen
    mMatrix = translationMatrix * mMatrix;
}

GLMatrix Model::getTransformation() const { return mMatrix; }

Material Model::getMaterial() const { return mMaterial; }
