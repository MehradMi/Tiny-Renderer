#include "renderer.h"
#include <SDL2/SDL_render.h>
#include <cstdlib>

Renderer::Renderer(Window *window, int index, uint32_t flags):
  m_renderer(nullptr),
  m_fail_flag(false)
{
  m_window = window;
  m_index  = index;
  m_flags  = flags;

  if (!create_renderer()) {
    set_fail_flag(true);
    exit(1);
  }
}

bool Renderer::create_renderer() {
  m_renderer = SDL_CreateRenderer(m_window->get_sdl_window(), m_index, m_flags);
  if (!m_renderer) {
    std::cerr << "ERROR::SDL::RENDERER_CREATION_FAILED" << std::endl;
    return false;
  }
  return true;
}

void Renderer::render() {
  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Renderer::get_sdl_renderer() {
  return m_renderer;
}

void Renderer::set_fail_flag(bool isFailed) {
  m_fail_flag = isFailed;
}

bool Renderer::get_fail_flag() {
  return m_fail_flag;
}
