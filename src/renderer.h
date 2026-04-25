#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <iostream>
#include "window.h"
#include "types.h"
#include "color_buffer_texture.h"
#include "color_buffer.h"

class Renderer {
  private:
    bool create_renderer();

    SDL_Renderer *m_renderer;
    int           m_index;      // renderer's index
    uint32_t      m_flags;      // renderer's flags to set
    Window       *m_window;     // window in which renderer runs

    ColorBuffer        *m_cb;   //
    ColorBufferTexture *m_cbt;  // 

  public:
    Renderer(Window *window, int index, uint32_t flags);

    void renderColorBuffer(void);

    SDL_Renderer* getSDLRenderer();   // get m_renderer

    void setColorBuffer(ColorBuffer *cb);
    void setColorBufferTexture(ColorBufferTexture *cbt);

    void drawRectangle(hex_color color, int x_pos, int y_pos, int w, int h);
};
#endif
