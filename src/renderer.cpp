#include "renderer.h"
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <cstdlib>

Renderer::Renderer(Window *window, int index, uint32_t flags):
  m_renderer(nullptr),
  m_cb(nullptr),
  m_cbt(nullptr)
{
  m_window = window;
  m_index  = index;
  m_flags  = flags;

  if (!create_renderer()) {
    exit(1);
  }
}

bool Renderer::create_renderer() {
  m_renderer = SDL_CreateRenderer(m_window->getSDLWindow(), m_index, m_flags);
  if (!m_renderer) {
    std::cerr << "ERROR::SDL::RENDERER_CREATION_FAILED" << std::endl;
    return false;
  }

  return true;
}

void Renderer::renderColorBuffer(void) {
  if (m_cbt != nullptr && m_cb != nullptr) {
    SDL_Texture *_cbt = m_cbt->getTexture();
    int _pitch = m_cb->getPitch();
    pixel *_cb = m_cb->getBuffer();
    SDL_UpdateTexture(_cbt, nullptr, _cb, _pitch);
    SDL_RenderCopy(m_renderer, _cbt, nullptr, nullptr);
  }
}

SDL_Renderer* Renderer::getSDLRenderer() {
  return m_renderer;
}

void Renderer::setColorBuffer(ColorBuffer *cb) {
  m_cb = cb;
}

void Renderer::setColorBufferTexture(ColorBufferTexture *cbt) {
  m_cbt = cbt;
}

/*
void Renderer::drawRectangle(hex_color color, int x_pos, int y_pos, int w, int h) {
  for (int i {0}; i < w; i++) {
    for (int j{0}; j < h; j++) {
      int cur_x = x_pos + i;
      int cur_y = y_pos + j;
      m_cb [ (cur_y * m_cb_width) + cur_x ] = color;
    }
  }
}
*/
