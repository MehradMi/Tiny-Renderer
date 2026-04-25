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

void ColorBuffer::drawPixel(hex_color color ,int x, int y) {
  try {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
      m_cb[ (m_width * y) + x] = color;
  } catch(const std::exception &e) {
    std::cerr << "ERROR::COLOR_BUFFER::COLOR_PIXEL FUNCTION FAILED: " << e.what() << std::endl;
  }
}

void ColorBuffer::clear(hex_color color) {
    for (int y{0}; y < m_height; y++)
      for (int x{0}; x < m_width; x++)
        drawPixel(color, x, y);
}

void ColorBuffer::drawGrid(hex_color color, int x_interval, int y_interval) {
  for (auto y{0}; y < m_height; y++)
    for (auto x{0}; x < m_width; x++)
      if (y % y_interval == 0 || x % x_interval == 0)
        drawPixel(color, x, y);
}

void ColorBuffer::drawRectangle(hex_color color, int x_pos, int y_pos, int w, int h) {
  for (int i {0}; i < w; i++) {
    for (int j{0}; j < h; j++) {
      int cur_x = x_pos + i;
      int cur_y = y_pos + j;
      drawPixel(color, cur_x, cur_y);
      //m_cb [ (cur_y * m_width) + cur_x ] = color;
    }
  }
}
