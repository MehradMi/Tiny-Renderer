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

    void clear(hex_color color);
    void drawPixel(hex_color color, int x, int y);
    void drawLine(hex_color color, int x0, int y0, int x1, int y1);
    void drawGrid(hex_color color, int x_interval = 10, int y_interval = 10);
    void drawRectangle(hex_color color, int x, int y, int w, int h);
    void drawTriangle(hex_color color, int x0, int y0, int x1, int y1, int x2, int y2);
};

#endif
