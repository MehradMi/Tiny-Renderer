#include "window.h"
#include <SDL2/SDL_video.h>

Window::Window():
  m_window(nullptr),
  m_flags(SDL_WINDOW_BORDERLESS),
  m_win_title("TinyRenderer"),
  m_width(500),
  m_height(500),
  m_posX(SDL_WINDOWPOS_CENTERED),
  m_posY(SDL_WINDOWPOS_CENTERED),
  m_fail_bit(false),
  m_should_close(false)
{
  create_window();
}

Window::Window(const char* title, int x, int y, int width, int height, int flags):
  m_window(nullptr),
  m_should_close(false)
{
  m_win_title = title;
  m_posX      = x;
  m_posY      = y;
  m_width     = width;
  m_height    = height;
  m_flags     = flags;

  if (!create_window()) {
    set_fail_bit(true);
    exit(1);
  }
}

bool Window::create_window() {
  // Initialize SDL (Everything)
  if (!SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "ERROR::SDL::SDL_INITIALIZATION_FAILED" << std::endl;
    return false;
  }

  // Create SDL Window
  m_window = SDL_CreateWindow(m_win_title, m_posX, m_posY, m_width, m_height, m_flags);
  if (!m_window) {
    std::cerr << "ERROR::SDL::WINDOW_CREATION_FAILED" << std::endl;
    return false;
  }

  return true;
}

int Window::get_width() {
  return m_width;
}

int Window::get_height() {
  return m_height;
}

SDL_Window* Window::get_sdl_window() {
  return m_window;
}

void Window::set_should_close(bool shouldClose) {
  m_should_close = shouldClose;
}

bool Window::get_should_close() {
  return m_should_close;
}

void Window::set_fail_bit(bool isFailed) {
  m_fail_bit = isFailed;
}
