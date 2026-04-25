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

void ColorBuffer::colorPixel(int x, int y, hex_color color) {
  try {
    m_cb[ (m_width * y) + x] = color;
  } catch(const std::exception &e) {
    std::cerr << "ERROR::COLOR_BUFFER::COLOR_PIXEL FUNCTION FAILED: " << e.what() << std::endl;
  }
}

void ColorBuffer::clear(hex_color color) {
    for (int y{0}; y < m_height; y++)
      for (int x{0}; x < m_width; x++)
        colorPixel(x, y, color);
}

void ColorBuffer::drawGrid(hex_color color, int x_interval, int y_interval) {
  for (auto y{0}; y < m_height; y++)
    for (auto x{0}; x < m_width; x++)
      if (y % y_interval == 0 || x % x_interval == 0)
        colorPixel(x, y, color);
}
