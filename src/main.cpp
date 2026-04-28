#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <sys/types.h>

#include "vector.h"
#include "window.h"
#include "renderer.h"
#include "color_buffer.h"
#include "color_buffer_texture.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

///////////////////////////////////////////////////////////////////////
// global vars
///////////////////////////////////////////////////////////////////////
ColorBuffer *CB;
ColorBufferTexture *CBT;

uint32_t previous_frame_time = SDL_GetTicks();

constexpr int VERTICES_COUNT = 9 * 9 * 9;
constexpr int FOV_FACTOR = 640;
Vec3D camera_position {0, 0,  -5};
Vec3D cube_rotation{0, 0, 0};
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
        0x0000FFFF,
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
  /*
  while(!SDL_TICKS_PASSED(SDL_GetTicks(), previous_frame_time + FRAME_TARGET_TIME));
  */ 

  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  previous_frame_time =  SDL_GetTicks();

  cube_rotation.x += 0.01;
  cube_rotation.y += 0.01;
  cube_rotation.z += 0.01;

  for (int i{0}; i < VERTICES_COUNT; i++) {
    Vec3D _vector = cube_vertices[i];

    _vector.Rotate(Axis::X, cube_rotation.x);
    _vector.Rotate(Axis::Y, cube_rotation.y);
    _vector.Rotate(Axis::Z, cube_rotation.z);

    // moving the vectors away from the camera
    _vector.z -= camera_position.z;

    //Vec2D _projected_point = orthographic_proj(_vector);
    Vec2D _projected_point = perspective_proj(_vector);
    //Vec2D _projected_point = perspective_proj(transformed_point);
    projected_vertices[i] = _projected_point;
  }
}

///////////////////////////////////////////////////////////////////////
