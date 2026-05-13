#ifndef VEC3D_H
#define VEC3D_H

#include <iostream>
#include <cmath>

enum Axis {
  X,
  Y,
  Z
};

struct Vec3D {
  float x;
  float y;
  float z;

  void Rotate(Axis a, float angle);
  void StrangeRotate(Axis a, float angle);

  Vec3D operator+(const Vec3D&) const;
  Vec3D operator-(const Vec3D&) const;
  Vec3D operator*(const float&) const;
  Vec3D operator/(const float&) const;

  static float length(Vec3D v);
  static Vec3D cross(Vec3D a, Vec3D b);
  static float dot(Vec3D a, Vec3D b);
  static void  normalize(Vec3D& v);
};

#endif
