#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

enum Axis {
  X,
  Y,
  Z
};

struct Vec2D {
  public:

    float x;
    float y;
};

struct Vec3D {
  public:

    float x;
    float y;
    float z;

    void Rotate(Axis a, float angle);
    void StrangeRotate(Axis a, float angle);
};


#endif
