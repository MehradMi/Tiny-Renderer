#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <iostream>
#include "window.h"

class Renderer {
  public:
    Renderer(Window *window, int index, uint32_t flags);

    void render();
    
    void set_fail_flag(bool isFailed);
    bool get_fail_flag();
    SDL_Renderer* get_sdl_renderer();   // get m_renderer

  private:
    bool create_renderer();

    SDL_Renderer *m_renderer;
    int           m_index;      // renderer's index
    uint32_t      m_flags;      // renderer's flags to set
    Window       *m_window;     // window in which renderer runs
    bool          m_fail_flag;  // renderer failure flag

};

#endif
