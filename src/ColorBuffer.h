#ifndef COLOR_BUFFER_H
#define COLOR_BUFFER_H

#include <SDL2/SDL_render.h>
#include <exception>
#include <iostream>
#include <memory>

#include "types.h"

class ColorBuffer {
private:
  int    m_width;
  int    m_height;
  int    m_pitch;
  std::unique_ptr<pixel[]> m_buffer;


public:
  ColorBuffer() = delete;
  ColorBuffer(const ColorBuffer&) = delete;
  ColorBuffer& operator=(const ColorBuffer&) = delete;
  ColorBuffer(ColorBuffer&&) noexcept;
  ColorBuffer& operator=(ColorBuffer&&) noexcept;
  ~ColorBuffer() = default;

  ColorBuffer(int w, int h);

  int getPitch()     { return m_pitch; }
  pixel* getBuffer() { return m_buffer.get(); }

  void setPixel(int x, int y, hex_color color);
  void clear(hex_color color);
};

#endif
