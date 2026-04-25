#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <sys/types.h>
#include "window.h"
#include "renderer.h"
#include "color_buffer.h"
#include "color_buffer_texture.h"

///////////////////////////////////////////////////////////////////////
// global vars
///////////////////////////////////////////////////////////////////////
ColorBuffer *CB;
ColorBufferTexture *CBT;
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// function declarations
///////////////////////////////////////////////////////////////////////
void setup(Window *window, Renderer *renderer);
void render(Renderer *renderer);

void process_input(Window *window);

void update(void); // TODO

void terminate(void); // TODO
///////////////////////////////////////////////////////////////////////

/*
void terminate_prog(void) {
  delete [] color_buffer;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
*/

int main() {

  Window *program_window = new Window(
      "Tiny Renderer",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1920, 1080,
      SDL_WINDOW_BORDERLESS);

  Renderer *program_renderer = new Renderer(
      program_window,
      -1, 
      0);

  setup(program_window, program_renderer);

  while (!program_window->getShouldClose()) {
    process_input(program_window);
    render(program_renderer);
  }

  //terminate_prog();

  return 0;
}

///////////////////////////////////////////////////////////////////////
// function definitions
///////////////////////////////////////////////////////////////////////
void setup(Window *window, Renderer *renderer) {
  CB = new ColorBuffer(window->getWidth(), window->getHeight());
  CBT = new ColorBufferTexture(
      renderer->getSDLRenderer(),
      window->getWidth(),
      window->getHeight(),
      SDL_TEXTUREACCESS_STATIC,
      SDL_PIXELFORMAT_ABGR8888);

  renderer->setColorBuffer(CB);
  renderer->setColorBufferTexture(CBT);
}

void render(Renderer *renderer) {
  SDL_Renderer *_renderer = renderer->getSDLRenderer();
  SDL_SetRenderDrawColor(
      renderer->getSDLRenderer(),
      255, 0, 0, 255);

  renderer->renderColorBuffer();
  CB->clear(0xFFFFFF00);
  SDL_RenderPresent(_renderer);
  SDL_RenderClear(_renderer);
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

///////////////////////////////////////////////////////////////////////
