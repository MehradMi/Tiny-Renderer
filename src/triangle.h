#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <utility>

#include "Vec2D.h"
#include "types.h"

struct Face {
  int a, b, c;
};

struct Triangle {
  Vec2D points[3];

  static void drawFilled(
    int x0, int y0,
    int x1, int y1,
    int x2, int y2,
    hex_color color
  );

private:
  static void sortVertices(
    int& x0, int& y0,
    int& x1, int& y1,
    int& x2, int& y2
  );

  static void flatBottom(
    int x0, int y0,
    int x1, int y1,
    int mx, int my,
    hex_color color
  );
};

#endif
