#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>
#include <iostream>

struct Vec2D {
  float x;
  float y;

  Vec2D operator+(const Vec2D&) const;
  Vec2D operator-(const Vec2D&) const;
  Vec2D operator*(const float&) const;
  Vec2D operator/(const float&) const;

  static float length(Vec2D v);
  static float dot(Vec2D a, Vec2D b);
  static void  normalize(Vec2D& v);
};

#endif
