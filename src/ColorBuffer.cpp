#include "ColorBuffer.h"

ColorBuffer::ColorBuffer(int w, int h):
  m_width(w),
  m_height(h),
  m_pitch(m_width * sizeof(pixel)),
  m_buffer(new pixel[m_width * m_height])
{
}

ColorBuffer::ColorBuffer(ColorBuffer&& other) noexcept :
  m_width(other.m_width),
  m_height(other.m_height),
  m_pitch(other.m_pitch),
  m_buffer(std::move(other.m_buffer))
{
  // Nullify "other"
  other.m_width  = 0;
  other.m_height = 0;
  other.m_pitch  = 0;
}

ColorBuffer& ColorBuffer::operator=(ColorBuffer&& other) noexcept {
  // Self-Assignment Check
  if (this == &other)
    return *this;

  // Steal the buffer pointer
  m_width  = other.m_width;
  m_height = other.m_height;
  m_pitch  = other.m_pitch;
  m_buffer = std::move(other.m_buffer);

  // Nullify the source ("other")
  other.m_width  = 0;
  other.m_height = 0;
  other.m_pitch  = 0;

  return *this;
}

void ColorBuffer::setPixel(int x, int y, hex_color color)
{
  try {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
      m_buffer[ (m_width * y) + x] = color;
  } catch(const std::exception &e) {
    std::cerr << "ERROR::COLOR_BUFFER::COLOR_PIXEL FUNCTION FAILED: " << e.what() << std::endl;
  }
}

void ColorBuffer::clear(hex_color color) {
    for (int y{0}; y < m_height; y++)
      for (int x{0}; x < m_width; x++)
        //setPixel(color, x, y);
        setPixel(x, y, color);
}
