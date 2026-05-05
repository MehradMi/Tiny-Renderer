#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>
#include <cmath>

enum Axis {
  X,
  Y,
  Z
};

struct Vec2D {
  float x;
  float y;
};

struct Vec3D {
  float x;
  float y;
  float z;

  void Rotate(Axis a, float angle);
  void StrangeRotate(Axis a, float angle);
};

float vec_length(Vec2D v);
float vec_length(Vec3D v);

Vec2D vec_add(Vec2D a, Vec2D b);
Vec3D vec_add(Vec3D a, Vec3D b);

Vec2D vec_sub(Vec2D a, Vec2D b);
Vec3D vec_sub(Vec3D a, Vec3D b);

Vec2D vec_smul(Vec2D a, float s);
Vec3D vec_smul(Vec3D a, float s);

Vec2D vec_sdiv(Vec2D a, float s);
Vec3D vec_sdiv(Vec3D a, float s);

Vec3D vec_cross(Vec3D a, Vec3D b);

float vec_dot(Vec2D a, Vec2D b);
float vec_dot(Vec3D a, Vec3D b);

void vec_normalize(Vec2D& v);
void vec_normalize(Vec3D& v);

#endif
