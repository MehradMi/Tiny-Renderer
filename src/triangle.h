#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vec2D.h"

struct Face {
  int a, b, c;
};

struct Triangle {
  Vec2D points[3];
};

#endif
