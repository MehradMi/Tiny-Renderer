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
    std::swap(x1, x2);
  }
  if (y0 > y1) {
    std::swap(y0, y1);
    std::swap(x0, x1);
  }
}

void Triangle::flatBottom(
  int x0, int y0,
  int x1, int y1,
  int mx, int my,
  hex_color color
)
{
  float slope_inv_1 = float(x1 - x0) / (y1 - y0);
  float slope_inv_2 = float(mx - x0) / (my - y0);

  // start x_start and x_end from the toppest vertex (x0, y0)
  float x_start = x0;
  float x_end   = x0;

  // NOTE: loop all the scanlines from top to bottom
  for (int y{y0}; y <= my; y++) {
    // TODO: drawLine(x_start, y, x_end, y, color);
    x_start += slope_inv_1;
    x_end   += slope_inv_2;
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
