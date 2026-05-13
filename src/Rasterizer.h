#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "ColorBuffer.h"
#include "types.h"

class Rasterizer {
private:
  ColorBuffer& m_colorBuffer;
  // TODO: Depth Buffer

public:
  Rasterizer(ColorBuffer& color_buffer);

  void drawLine(
    int x0, int y0,
    int x1, int y1,
    hex_color color
  );

  void drawCircle(
    int cx, int cy,
    int r,
    hex_color color
  );

  void drawGrid(
    int x_interval = 10, int y_interval = 10,
    hex_color color = 0xFF000000
  );

  void drawRectangle(
    int x, int y,
    int w, int h,
    hex_color color
  );

  void drawTriangle(
    int x0, int y0,
    int x1, int y1,
    int x2, int y2,
    hex_color color
  );
};

#endif
