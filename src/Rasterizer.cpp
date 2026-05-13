#include "Rasterizer.h"

Rasterizer::Rasterizer(ColorBuffer& color_buffer):
  m_colorBuffer(color_buffer)
{
}

void Rasterizer::drawLine(
  int x0, int y0,
  int x1, int y1,
  hex_color color
)
{
  int delta_x = (x1 - x0);
  int delta_y = (y1 - y0);

  int longest_side_length =
    (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

  float x_inc = delta_x / (float)longest_side_length;
  float y_inc = delta_y / (float)longest_side_length;

  float cur_x = x0;
  float cur_y = y0;
  for (int i{0}; i <= longest_side_length; i++) {
    m_colorBuffer.setPixel(round(cur_x), round(cur_y), color);
    cur_x += x_inc;
    cur_y += y_inc;
  }
}

void Rasterizer::drawCircle(
  int cx, int cy,
  int r,
  hex_color color
)
{
  int x = 0;
  int y = r;
  int d = 3 - (2 * r);

  // plot 8 pixel
  while (x <= y) {
    // Plot 8 symmetric points around (cx, cy)
    m_colorBuffer.setPixel(cx + x, cy + y, color);
    m_colorBuffer.setPixel(cx + y, cy + x, color);
    
    m_colorBuffer.setPixel(cx - x, cy + y, color);
    m_colorBuffer.setPixel(cx + y, cy - x, color);
    
    m_colorBuffer.setPixel(cx + x, cy - y, color);
    m_colorBuffer.setPixel(cx - y, cy + x, color);
    
    m_colorBuffer.setPixel(cx - x, cy - y, color);
    m_colorBuffer.setPixel(cx - y, cy - x, color);

    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d += 4 * (x - y) + 10;
      y--;
    }
    x++;
  }
}

/*
void Rasterizer::drawGrid(
  int x_interval, int y_interval,
  hex_color color
)
{
  for (auto y{0}; y < m_height; y++)
    for (auto x{0}; x < m_width; x++)
      if (y % y_interval == 0 || x % x_interval == 0)
        setPixel(color, x, y);
}
*/

void Rasterizer::drawRectangle(
  int x, int y,
  int w, int h,
  hex_color color
)
{
  for (int i {0}; i < w; i++) {
    for (int j{0}; j < h; j++) {
      int cur_x = x + i;
      int cur_y = y + j;
      m_colorBuffer.setPixel(cur_x, cur_y, color);
    }
  }
}

void Rasterizer::drawTriangle(
  int x0, int y0,
  int x1, int y1,
  int x2, int y2,
  hex_color color
)
{
  drawLine(x0, y0, x1, y1, color);
  drawLine(x1, y1, x2, y2, color);
  drawLine(x2, y2, x0, y0, color);
}
