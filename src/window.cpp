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
  if (!initialize_sdl()) {
    set_fail_bit(true);
    exit(1);
  }

  if (!create_window()) {
    set_fail_bit(true);
    exit(1);
  }
}

Window::Window(const char* title, int x, int y, int flags):
  m_window(nullptr),
  m_should_close(false)
{
  if (!initialize_sdl()) {
    set_fail_bit(true);
    exit(1);
  }

  m_win_title = title;
  m_posX      = x;
  m_posY      = y;
  m_flags = flags;

  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);
  m_width  = display_mode.w;
  m_height = display_mode.h;

  if (!create_window()) {
    set_fail_bit(true);
    exit(1);
  } else {
    std::cout << m_width << " " << m_height << std::endl;
  }
}

Window::Window(const char* title, int x, int y, int width, int height, int flags):
  m_window(nullptr),
  m_should_close(false)
{
  if (!initialize_sdl()) {
    set_fail_bit(true);
    exit(1);
  }

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

bool Window::initialize_sdl() {
  // Initialize SDL (Everything)
  if (!SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "ERROR::SDL::SDL_INITIALIZATION_FAILED" << std::endl;
    return false;
  }

  return true;
}

bool Window::create_window() {
  // Create SDL Window
  m_window = SDL_CreateWindow(m_win_title, m_posX, m_posY, m_width, m_height, m_flags);
  if (!m_window) {
    std::cerr << "ERROR::SDL::WINDOW_CREATION_FAILED" << std::endl;
    return false;
  }

  return true;
}

SDL_Window* Window::getSDLWindow() {
  return m_window;
}

void Window::setShouldClose(bool shouldClose) {
  m_should_close = shouldClose;
}

bool Window::getShouldClose() {
  return m_should_close;
}

void Window::set_fail_bit(bool isFailed) {
  m_fail_bit = isFailed;
}
