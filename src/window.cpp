#include "Window.h"
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
  if (!initSDL())
    exit(1);

  if (!create())
    exit(1);
}

Window::Window(const char* title, int x, int y, int flags):
  m_window(nullptr),
  m_should_close(false)
{
  if (!initSDL())
    exit(1);

  m_win_title = title;
  m_posX      = x;
  m_posY      = y;
  m_flags = flags;

  SDL_DisplayMode display_mode;
  SDL_GetCurrentDisplayMode(0, &display_mode);
  m_width  = display_mode.w;
  m_height = display_mode.h;

  if (!create())
    exit(1);
  else
    std::cout << m_width << " " << m_height << std::endl;
}

Window::Window(const char* title, int x, int y, int width, int height, int flags):
  m_window(nullptr),
  m_should_close(false)
{
  if (!initSDL())
    exit(1);

  m_win_title = title;
  m_posX      = x;
  m_posY      = y;
  m_width     = width;
  m_height    = height;
  m_flags     = flags;

  if (!create())
    exit(1);
}

Window::~Window() {
  if (m_window) {
    SDL_DestroyWindow(m_window);
    m_window = nullptr;
  }

  SDL_Quit();
}

/*
void Window::process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      this->setShouldClose(true);
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) 
        window->setShouldClose(true);
      break;
  }
}
*/

bool Window::initSDL() {
  // Initialize SDL (Everything)
  if (!SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "ERROR::SDL::SDL_INITIALIZATION_FAILED" << std::endl;
    return false;
  }

  return true;
}

bool Window::create() {
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
