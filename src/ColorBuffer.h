#ifndef COLOR_BUFFER_H
#define COLOR_BUFFER_H

#include <SDL2/SDL_render.h>
#include <exception>
#include <iostream>
#include <new>

#include "types.h"

class ColorBuffer {
  private:
    int    m_width;
    int    m_height;
    int    m_pitch;
    pixel *m_cb;


  public:
    ColorBuffer(int w, int h);
    ~ColorBuffer();

    int getPitch()     { return m_pitch; }
    pixel* getBuffer() { return m_cb; }

    void setPixel(int x, int y, hex_color color);
    void clear(hex_color color);
};

#endif
