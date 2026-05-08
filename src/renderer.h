#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <iostream>

#include "Window.h"
#include "types.h"
#include "ColorBufferTexture.h"
#include "ColorBuffer.h"

class Renderer {
  private:
    bool create();

    SDL_Renderer *m_renderer;
    int           m_index;      // renderer's index
    uint32_t      m_flags;      // renderer's flags to set
    Window       *m_window;     // window in which renderer runs

    ColorBuffer        *m_cb;
    ColorBufferTexture *m_cbt;

  public:
    Renderer(Window *window, int index, uint32_t flags);
    ~Renderer();

    void renderColorBuffer(void);

    SDL_Renderer* getSDLRenderer();   // get m_renderer

    void setColorBuffer(ColorBuffer *cb);
    void setColorBufferTexture(ColorBufferTexture *cbt);
};
#endif
