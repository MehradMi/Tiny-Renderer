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

  static float length(Vec3D v);
  static Vec3D add(Vec3D a, Vec3D b);
  static Vec3D sub(Vec3D a, Vec3D b);
  static Vec3D mul(Vec3D a, float s);
  static Vec3D div(Vec3D a, float s);
  static Vec3D cross(Vec3D a, Vec3D b);
  static float dot(Vec3D a, Vec3D b);
  static void  normalize(Vec3D& v);
};

#endif
