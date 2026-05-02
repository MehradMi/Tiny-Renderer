#include "color_buffer.h"

ColorBuffer::ColorBuffer(int w, int h):
  m_width(w),
  m_height(h),
  m_pitch(m_width * sizeof(pixel)),
  m_cb(nullptr)
{
  if (m_width && m_height) {
    try {
      m_cb = new (std::nothrow) pixel[m_width * m_height];
    } catch (const std::exception& e) {
      std::cerr << "ERROR::COLOR_BUFFER::COLOR_BUFFER CONSTRUCTOR FAILED: " << e.what() << std::endl;
      return;
    }
  }

  return;
}

int ColorBuffer::getPitch() {
  return m_pitch;
}

pixel* ColorBuffer::getBuffer() {
  return m_cb;
}

void ColorBuffer::clear(hex_color color) {
    for (int y{0}; y < m_height; y++)
      for (int x{0}; x < m_width; x++)
        drawPixel(color, x, y);
}

void ColorBuffer::drawPixel(
  hex_color color,
  int x, int y)
{
  try {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
      m_cb[ (m_width * y) + x] = color;
  } catch(const std::exception &e) {
    std::cerr << "ERROR::COLOR_BUFFER::COLOR_PIXEL FUNCTION FAILED: " << e.what() << std::endl;
  }
}

void ColorBuffer::drawLine(
  hex_color color,
  int x0, int y0,
  int x1, int y1)
{
  int delta_x = (x1 - x0);
  int delta_y = (y1 - y0);

  int longest_side_length = 
    (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

  float x_inc = delta_x / (float)longest_side_length;
  float y_inc = delta_y / (float)longest_side_length;

  float current_x = x0;
  float current_y = y0;
  for (int i{0}; i <= longest_side_length; i++) {
    drawPixel(color, round(current_x), round(current_y));
    current_x += x_inc;
    current_y += y_inc;
  }
}

void ColorBuffer::drawGrid(
  hex_color color,
  int x_interval, int y_interval) 
{
  for (auto y{0}; y < m_height; y++)
    for (auto x{0}; x < m_width; x++)
      if (y % y_interval == 0 || x % x_interval == 0)
        drawPixel(color, x, y);
}

void ColorBuffer::drawRectangle(
  hex_color color, 
  int x_pos, int y_pos, 
  int w, int h)
{
  for (int i {0}; i < w; i++) {
    for (int j{0}; j < h; j++) {
      int cur_x = x_pos + i;
      int cur_y = y_pos + j;
      drawPixel(color, cur_x, cur_y);
    }
  }
}


void ColorBuffer::drawTriangle(
  hex_color color,
  int x0, int y0, 
  int x1, int y1, 
  int x2, int y2)
{
  drawLine(color, x0, y0, x1, y1);
  drawLine(color, x1, y1, x2, y2);
  drawLine(color, x2, y2, x0, y0);
}
