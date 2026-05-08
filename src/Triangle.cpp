#include "Triangle.h"

void Triangle::sortVertices(
  int& x0, int& y0,
  int& x1, int& y1,
  int& x2, int& y2
)
{
  if (y0 > y1) {
    std::swap(y0, y1);
    std::swap(x0, x1);
  }
  if (y1 > y2) {
    std::swap(y1, y2);
    std::swap(x2, x2);
  }
  if (y0 > y1) {
    std::swap(y0, y1);
    std::swap(x0, x1);
  }
}

void Triangle::drawFilled(
  int x0, int y0,
  int x1, int y1,
  int x2, int y2,
  hex_color color
)
{
  // sort vertices by "y" in ascending order (y0 < y1 < y2)
  Triangle::sortVertices(x0, y0, x1, y1, x2, y2);

  // TODO: Find (Mx, My)
  int My = y1;
  int Mx = x0 + ((x2 - x0) * (y1 - y0) / (y2 - y0));

  // TODO: Draw Flat-Bottom
  
  // TODO: Draw Flat-Top
}
