#ifndef VEC2D_H
#define VEC2D_H

#include <cmath>
#include <iostream>

struct Vec2D {
  float x;
  float y;

  static float length(Vec2D v);
  static Vec2D add(Vec2D a, Vec2D b);
  static Vec2D sub(Vec2D a, Vec2D b);
  static Vec2D mul(Vec2D a, float s);
  static Vec2D div(Vec2D a, float s);
  static float dot(Vec2D a, Vec2D b);
  static void  normalize(Vec2D& v);
};

#endif
