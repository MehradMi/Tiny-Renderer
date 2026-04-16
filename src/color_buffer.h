#ifndef COLOR_BUFFER_H
#define COLOR_BUFFER_H

#include <cstdint>
#include <SDL2/SDL.h>
#include "renderer.h"

using pixel = uint32_t; // each pixel is of "uint32_t" type. uint32_t = 4 bytes
using hex_color = uint32_t;

class ColorBuffer {
  public:
    ColorBuffer();
    ColorBuffer(int buffer_width, int buffer_height);

    void create_buffer_texture(Renderer *renderer, uint32_t tex_format, int access, int tex_width, int tex_height);
    void clear_buffer(hex_color color);
    void paint_pixel(int x, int y, hex_color);
    void render(Renderer *renderer); // render color buffer

  private:
    pixel       *m_buffer;
    SDL_Texture *m_buffer_texture;
    int          m_width;
    int          m_height;

    void create_buffer();
};

#endif
