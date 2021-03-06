#pragma once

#include <array>
#include <vector>
#include <limits>
#include <memory>

#include "GLMatrix.hpp"
#include "GLPoint.hpp"
#include "GLVector.hpp"

inline GLVector operator*(const GLVector &lhs, double scale) {
  return GLVector(lhs(0) * scale, lhs(1) * scale, lhs(2) * scale);
}

inline GLVector operator*(double scale, const GLVector &rhs) {
  return GLVector(rhs(0) * scale, rhs(1) * scale, rhs(2) * scale);
}

inline GLPoint operator*(const GLPoint &lhs, double scale) {
  return GLPoint(lhs(0) * scale, lhs(1) * scale, lhs(2) * scale);
}

inline GLPoint operator*(double scale, const GLPoint &rhs) {
  return GLPoint(rhs(0) * scale, rhs(1) * scale, rhs(2) * scale);
}

inline GLPoint operator+(const GLPoint &p1, const GLVector &p2) {
  return GLPoint(p1(0) + p2(0), p1(1) + p2(1), p1(2) + p2(2));
}

inline GLPoint operator-(const GLPoint &p1, const GLVector &p2) {
  return GLPoint(p1(0) - p2(0), p1(1) - p2(1), p1(2) - p2(2));
}

inline GLPoint operator+(const GLPoint &p1, const GLPoint &p2) {
  return GLPoint(p1(0) + p2(0), p1(1) + p2(1), p1(2) + p2(2));
}

inline GLVector operator+(const GLVector &p1, const GLVector &p2) {
  return GLVector(p1(0) + p2(0), p1(1) + p2(1), p1(2) + p2(2));
}

inline GLVector operator-(const GLPoint &p1, const GLPoint &p2) {
  return GLVector(p1(0) - p2(0), p1(1) - p2(1), p1(2) - p2(2));
}

inline GLVector crossProduct(const GLVector &lhs, const GLVector &rhs) {
  return GLVector(lhs(1) * rhs(2) - lhs(2) * rhs(1),
                  lhs(2) * rhs(0) - lhs(0) * rhs(2),
                  lhs(0) * rhs(1) - lhs(1) * rhs(0));
}

inline double dotProduct(const GLVector &lhs, const GLVector &rhs) {
  return lhs(0) * rhs(0) + lhs(1) * rhs(1) + lhs(2) * rhs(2);
}

inline int sgn(int x) { return (x > 0) ? 1 : (x < 0) ? -1 : 0; }

/** Aufgabenblatt 2, Aufgabe 2 **/

inline GLVector operator*(const GLMatrix &m1, const GLVector &rhs){
    return GLVector(m1(0,0) * rhs(0) + m1(0,1) * rhs(1) + m1(0,2) * rhs(2) + m1(0,3) * 1.0,
                    m1(1,0) * rhs(0) + m1(1,1) * rhs(1) + m1(1,2) * rhs(2) + m1(1,3) * 1.0,
                    m1(2,0) * rhs(0) + m1(2,1) * rhs(1) + m1(2,2) * rhs(2) + m1(2,3) * 1.0);
}

inline GLPoint operator*(const GLMatrix &m1, const GLPoint &p1){
    return GLPoint(m1(0,0) * p1(0) + m1(0,1) * p1(1) + m1(0,2) * p1(2) + m1(0,3) * 1.0,
                   m1(1,0) * p1(0) + m1(1,1) * p1(1) + m1(1,2) * p1(2) + m1(1,3) * 1.0,
                   m1(2,0) * p1(0) + m1(2,1) * p1(1) + m1(2,2) * p1(2) + m1(2,3) * 1.0);
}


inline GLMatrix operator*(const GLMatrix &m1, const GLMatrix &m2){
    GLMatrix m3;
    m3.setValue(0,0, m1(0,0) * m2(0,0) + m1(0,1) * m2(1,0) + m1(0,2) * m2(2,0) + m1(0,3) * m2(3,0));
    m3.setValue(0,1, m1(0,0) * m2(0,1) + m1(0,1) * m2(1,1) + m1(0,2) * m2(2,1) + m1(0,3) * m2(3,1));
    m3.setValue(0,2, m1(0,0) * m2(0,2) + m1(0,1) * m2(1,2) + m1(0,2) * m2(2,2) + m1(0,3) * m2(3,2));
    m3.setValue(0,3, m1(0,0) * m2(0,3) + m1(0,1) * m2(1,3) + m1(0,2) * m2(2,3) + m1(0,3) * m2(3,3));

    m3.setValue(1,0, m1(1,0) * m2(0,0) + m1(1,1) * m2(1,0) + m1(1,2) * m2(2,0) + m1(1,3) * m2(3,0));
    m3.setValue(1,1, m1(1,0) * m2(0,1) + m1(1,1) * m2(1,1) + m1(1,2) * m2(2,1) + m1(1,3) * m2(3,1));
    m3.setValue(1,2, m1(1,0) * m2(0,2) + m1(1,1) * m2(1,2) + m1(1,2) * m2(2,2) + m1(1,3) * m2(3,2));
    m3.setValue(1,3, m1(1,0) * m2(0,3) + m1(1,1) * m2(1,3) + m1(1,2) * m2(2,3) + m1(1,3) * m2(3,3));

    m3.setValue(2,0, m1(2,0) * m2(0,0) + m1(2,1) * m2(1,0) + m1(2,2) * m2(2,0) + m1(2,3) * m2(3,0));
    m3.setValue(2,1, m1(2,0) * m2(0,1) + m1(2,1) * m2(1,1) + m1(2,2) * m2(2,1) + m1(2,3) * m2(3,1));
    m3.setValue(2,2, m1(2,0) * m2(0,2) + m1(2,1) * m2(1,2) + m1(2,2) * m2(2,2) + m1(2,3) * m2(3,2));
    m3.setValue(2,3, m1(2,0) * m2(0,3) + m1(2,1) * m2(1,3) + m1(2,2) * m2(2,3) + m1(2,3) * m2(3,3));

    m3.setValue(3,0, m1(3,0) * m2(0,0) + m1(3,1) * m2(1,0) + m1(3,2) * m2(2,0) + m1(3,3) * m2(3,0));
    m3.setValue(3,1, m1(3,0) * m2(0,1) + m1(3,1) * m2(1,1) + m1(3,2) * m2(2,1) + m1(3,3) * m2(3,1));
    m3.setValue(3,2, m1(3,0) * m2(0,2) + m1(3,1) * m2(1,2) + m1(3,2) * m2(2,2) + m1(3,3) * m2(3,2));
    m3.setValue(3,3, m1(3,0) * m2(0,3) + m1(3,1) * m2(1,3) + m1(3,2) * m2(2,3) + m1(3,3) * m2(3,3));
    return m3;
}
