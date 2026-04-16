#include <SDL2/SDL.h>
#include <cstdint>
#include "window.h"
#include "renderer.h"
#include "color_buffer.h"

uint32_t *color_buffer {nullptr};
SDL_Texture *color_buffer_texture {nullptr};

/*
void setup_prog(void) {
  color_buffer = new (std::nothrow) uint32_t[800 * 600];

  color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 800, 600);
}
*/

/*
void terminate_prog(void) {
  delete [] color_buffer;
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
*/

void process_input(Window *window) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      window->set_should_close(true);
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) 
        window->set_should_close(true);
      break;
  }
}

void update(void) {
  // TODO
}

/*
void render_color_buffer(void) {
  SDL_UpdateTexture(color_buffer_texture, nullptr, color_buffer, 800 * sizeof(uint32_t));
  SDL_RenderCopy(renderer, color_buffer_texture, nullptr, nullptr);
}
*/

void clear_color_buffer(uint32_t color) {
  for (auto y{0}; y < 600; y++) {
    for (auto x{0}; x < 800; x++) {
      color_buffer[(800 * y) + x] = color;
    }
  }
}

/*
void render(void) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);

  render_color_buffer();
  clear_color_buffer(0xFFFFFF00);

  SDL_RenderPresent(renderer);
}
*/

int main() {

  Window      *program_window = new Window("Tiny Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_BORDERLESS);
  Renderer    *program_renderer       = new Renderer(program_window, -1, 0);
  ColorBuffer *color_buffer   = new ColorBuffer(program_window->get_width(), program_window->get_height());

  //setup_prog();

  while (!program_window->get_should_close()) {
    process_input(program_window);
    program_renderer->render();
    color_buffer->render(program_renderer);
    color_buffer->clear_buffer(0xFFFFFF00);
  }

  //terminate_prog();

  return 0;
}
