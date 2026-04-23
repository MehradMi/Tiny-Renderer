#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <sys/types.h>
#include "window.h"
#include "renderer.h"

void initialize_cb(Renderer *renderer, uint32_t cbt_format, int access);

/*
void terminate_prog(void) {
  delete [] color_buffer;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
*/

void process_input(Window *window);

void update(void);

int main() {

  Window      *program_window = new Window(
      "Tiny Renderer",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1920, 1080,
      SDL_WINDOW_BORDERLESS);

  Renderer    *program_renderer       = new Renderer(program_window, -1, 0);

  program_renderer->setCBResolution(program_window->getWidth(), program_window->getHeight());
  program_renderer->setCBTResolution(program_window->getWidth(), program_window->getHeight());

  initialize_cb(
      program_renderer,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STATIC);

  while (!program_window->getShouldClose()) {
    process_input(program_window);
    program_renderer->render();
  }

  //terminate_prog();

  return 0;
}


void initialize_cb(Renderer *renderer, uint32_t cbt_format, int access) {
  renderer->genColorBuffer();
  renderer->genColorBufferTexture(cbt_format, access);
}

void process_input(Window *window) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      window->setShouldClose(true);
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) 
        window->setShouldClose(true);
      break;
  }
}

void update(void) {
  // TODO
}
