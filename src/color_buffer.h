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

    int getPitch();
    pixel* getBuffer();

    void colorPixel(int x, int y, hex_color color);
    void clear(hex_color color);
    void drawGrid(hex_color color, int x_interval = 10, int y_interval = 10);
};

#endif
