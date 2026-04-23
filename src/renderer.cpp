#include "renderer.h"
#include "types.h"
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <cstdlib>

Renderer::Renderer(Window *window, int index, uint32_t flags):
  m_renderer(nullptr),
  m_fail_flag(false),
  m_cb_width(0),
  m_cb_height(0),
  m_cb(nullptr),
  m_cbt(nullptr)
{
  m_window = window;
  m_index  = index;
  m_flags  = flags;

  if (!create_renderer()) {
    setFailFlag(true);
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

void Renderer::render() {
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  renderColorBuffer();
  //clearCB(0xFFFFF00);
  //drawGrid(0xFFFFF00);
  drawRectangle(0xFFFFF00, 50, 50, 600, 400);

  SDL_RenderPresent(m_renderer);
}

void Renderer::renderColorBuffer(void) {
  if (m_cbt != nullptr && m_cb != nullptr) {
    SDL_UpdateTexture(m_cbt, nullptr, m_cb, m_cb_width * sizeof(pixel));
    SDL_RenderCopy(m_renderer, m_cbt, nullptr, nullptr);
  }
}

SDL_Renderer* Renderer::getSDLRenderer() {
  return m_renderer;
}

void Renderer::setFailFlag(bool isFailed) {
  m_fail_flag = isFailed;
}

bool Renderer::getFailFlag() {
  return m_fail_flag;
}

void Renderer::setCBResolution(int w, int h) {
  m_cb_width  = w;
  m_cb_height = h;
}

void Renderer::setCBTResolution(int w, int h) {
  m_cbt_width = w;
  m_cbt_height = h;
}

void Renderer::genColorBuffer() {
  if (m_cb_width == 0 || m_cb_height == 0) {
    m_cb = nullptr;
    return;
  }

  m_cb = new (std::nothrow) uint32_t[m_cb_width * m_cb_height];
}

void Renderer::genColorBufferTexture(uint32_t cbt_format, int access) {
  if (m_cbt_width == 0 || m_cbt_width == 0) {
    m_cbt = nullptr;
    return;
  }

  m_cbt = SDL_CreateTexture(m_renderer, cbt_format, access, m_cbt_width, m_cbt_height);
}

void Renderer::clearCB(hex_color color) {
  for (auto y{0}; y < m_cb_height; y++) {
    for (auto x{0}; x < m_cb_width; x++) {
      m_cb[ (y * m_cb_width) + x ] = color;
    }
  }
}

void Renderer::drawGrid(hex_color color) {
  for (auto y{0}; y < m_cb_height; y++) {
    for (auto x{0}; x < m_cb_width; x++) {
      if (y % 10 == 0 || x % 10 == 0)
        m_cb[ (y * m_cb_width) + x ] = color;
    }
  }
}

void Renderer::drawRectangle(hex_color color, int x_pos, int y_pos, int w, int h) {
  for (int i {0}; i < w; i++) {
    for (int j{0}; j < h; j++) {
      int cur_x = x_pos + i;
      int cur_y = y_pos + j;
      m_cb [ (cur_y * m_cb_width) + cur_x ] = color;
    }
  }
}
