#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <sys/types.h>

#include "vector.h"
#include "window.h"
#include "renderer.h"
#include "color_buffer.h"
#include "color_buffer_texture.h"

///////////////////////////////////////////////////////////////////////
// global vars
///////////////////////////////////////////////////////////////////////
ColorBuffer *CB;
ColorBufferTexture *CBT;

constexpr int VERTICES_COUNT = 9 * 9 * 9;
constexpr int FOV_FACTOR = 640;
Vec3D camera_position {0, 0,  -5};
Vec3D cube_vertices[VERTICES_COUNT];
Vec2D projected_vertices[VERTICES_COUNT];
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// function declarations
///////////////////////////////////////////////////////////////////////
void setup(Window *window, Renderer *renderer);
void render(Window *window, Renderer *renderer);

Vec2D orthographic_proj(Vec3D vector);
Vec2D perspective_proj(Vec3D vector);

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
    render(program_window , program_renderer);
    update();
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

  // populate the cube vertices ranging from -1 to +1
  int point_count = 0;
  for (float x{-1}; x <= 1; x += .25f) {
    for (float y{-1}; y <= 1; y += .25f) {
      for (float z{-1}; z <= 1; z += .25f) {
        Vec3D new_vector{ x, y ,z};
        cube_vertices[point_count++] = new_vector;
      }
    }
  }
}

Vec2D orthographic_proj(Vec3D vector) {
  Vec2D _projected_point{
    vector.x * FOV_FACTOR,
    vector.y * FOV_FACTOR 
  };

  return _projected_point;
}

Vec2D perspective_proj(Vec3D vector) {
  /*
  Vec2D _projected_point {
    (vector.x * FOV_FACTOR) / (vector.z ? vector.z: 1),
    (vector.y * FOV_FACTOR) / (vector.z ? vector.z: 1)
  };
  */
  Vec2D _projected_point {
    (vector.x * FOV_FACTOR) / vector.z,
    (vector.y * FOV_FACTOR) / vector.z
  };

  return _projected_point;
}

void render(Window *window ,Renderer *renderer) {
  SDL_Renderer *_sdl_renderer = renderer->getSDLRenderer();

  // loop all projected_vertices and render them
  for (int i{0}; i < VERTICES_COUNT; i++) {
    Vec2D _projected_vector = projected_vertices[i];
    CB->drawRectangle(
        0xFFFFFF00,
        _projected_vector.x + window->getWidth() / 2, 
        _projected_vector.y + window->getHeight() / 2,
        4,
        4
        );
  }

  renderer->renderColorBuffer();
  CB->clear(0xFF000000);
  SDL_RenderPresent(_sdl_renderer);
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
  for (int i{0}; i < VERTICES_COUNT; i++) {
    Vec3D _vector = cube_vertices[i];

    // moving the vectors away from the camera
    _vector.z -= camera_position.z;

    //Vec2D _projected_point = orthographic_proj(_vector);
    Vec2D _projected_point = perspective_proj(_vector);
    projected_vertices[i] = _projected_point;
  }
}

///////////////////////////////////////////////////////////////////////
