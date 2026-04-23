#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <iostream>
#include "window.h"
#include "types.h"

class Renderer {
  private:
    bool create_renderer();

    SDL_Renderer *m_renderer;
    int           m_index;      // renderer's index
    uint32_t      m_flags;      // renderer's flags to set
    Window       *m_window;     // window in which renderer runs
    bool          m_fail_flag;  // renderer failure flag

    /*
     * Color Buffer Related */
    int          m_cb_width;
    int          m_cb_height;
    pixel       *m_cb;

    int          m_cbt_width;
    int          m_cbt_height;
    SDL_Texture *m_cbt;

  public:
    Renderer(Window *window, int index, uint32_t flags);

    void render();
    void renderColorBuffer();
    
    void setFailFlag(bool isFailed);
    bool getFailFlag();
    SDL_Renderer* getSDLRenderer();   // get m_renderer

    void setCBResolution(int w, int h);
    void setCBTResolution(int w, int h);

    void genColorBuffer();
    void genColorBufferTexture(uint32_t cbt_format, int access);

    void clearCB(hex_color color);
    void drawGrid(hex_color color);
    void drawRectangle(hex_color color, int x_pos, int y_pos, int w, int h);
};
#endif
