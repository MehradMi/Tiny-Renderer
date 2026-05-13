#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <sys/types.h>
#include <vector>

#include "Triangle.h"
#include "Vec2D.h"
#include "Vec3D.h"
#include "Window.h"
#include "renderer.h"
#include "Rasterizer.h"
#include "ColorBuffer.h"
#include "ColorBufferTexture.h"
#include "Mesh.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

///////////////////////////////////////////////////////////////////////
Rasterizer  *RS;
ColorBuffer *CB;
ColorBufferTexture *CBT;

uint32_t previous_frame_time = SDL_GetTicks();

constexpr int VERTICES_COUNT = 9 * 9 * 9;
constexpr int FOV_FACTOR = 640;
Vec3D camera_position {0, 0,  0};
Vec2D projected_vertices[VERTICES_COUNT];

std::vector<Triangle> triangles_to_render;

Mesh cubeMesh("./assets/cube.obj");
Mesh diabloMesh("./assets/diablo3_post.obj");
Mesh f22Mesh("./assets/f22.obj");
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
void render(Window *window, Renderer *renderer);
void setup(Window *window, Renderer *renderer);

Vec2D orthographic_proj(Vec3D vector);
Vec2D perspective_proj(Vec3D vector);

void process_input(Window *window);

void update(Window *window);

void terminate(void); // TODO: implement this sucker
///////////////////////////////////////////////////////////////////////

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
    update(program_window);
    render(program_window , program_renderer);
  }

  cubeMesh.vertices.clear();
  cubeMesh.faces.clear();

  return 0;
}

void setup(Window *window, Renderer *renderer) {
  CB = new ColorBuffer(window->getWidth(), window->getHeight());
  CBT = new ColorBufferTexture(
      renderer->getSDLRenderer(),
      window->getWidth(),
      window->getHeight(),
      SDL_TEXTUREACCESS_STATIC,
      SDL_PIXELFORMAT_ABGR8888);

  RS = new Rasterizer(*CB);

  renderer->setColorBuffer(CB);
  renderer->setColorBufferTexture(CBT);
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

  int num_triangles = triangles_to_render.size();
  for (int i{0}; i < num_triangles; i++) {
    Triangle _triangle = triangles_to_render[i];
    RS->drawRectangle(
        _triangle.points[0].x,
        _triangle.points[0].y,
        4, 4,
        0x0000FFFF
        );
    RS->drawRectangle(
        _triangle.points[1].x,
        _triangle.points[1].y,
        4, 4,
        0x0000FFFF
        );
    RS->drawRectangle(
        _triangle.points[2].x,
        _triangle.points[2].y,
        4, 4,
        0x0000FFFF
        );

    // draw unfilled triangle
    RS->drawTriangle(
      _triangle.points[0].x, _triangle.points[0].y,
      _triangle.points[1].x, _triangle.points[1].y,
      _triangle.points[2].x, _triangle.points[2].y,
      0x0000FFFF
    );
  }

  triangles_to_render.clear();

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

void update(Window *window) {

  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);

  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  previous_frame_time =  SDL_GetTicks();

  cubeMesh.rotation.x += 0.01;
  cubeMesh.rotation.y += 0.01;
  cubeMesh.rotation.z += 0.01;

  int num_faces = cubeMesh.faces.size();
  for (int i{0}; i < num_faces; i++) {
    Face mesh_face = cubeMesh.faces[i];

    Vec3D face_vertices[3];
    face_vertices[0] = cubeMesh.vertices[mesh_face.a - 1];
    face_vertices[1] = cubeMesh.vertices[mesh_face.b - 1];
    face_vertices[2] = cubeMesh.vertices[mesh_face.c - 1];

    Vec3D transformed_vertices[3];

    // loop all three vertices of this current face and apply transformation
    for (int j{0}; j < 3; j++) {
      Vec3D _transformed_vertex = face_vertices[j];

      _transformed_vertex.Rotate(Axis::X, cubeMesh.rotation.x);
      _transformed_vertex.Rotate(Axis::Y, cubeMesh.rotation.y);
      _transformed_vertex.Rotate(Axis::Z, cubeMesh.rotation.z);

      /*
      _transformed_vertex.StrangeRotate(Axis::X, cubeMesh.rotation.x);
      _transformed_vertex.StrangeRotate(Axis::Y, cubeMesh.rotation.y);
      _transformed_vertex.StrangeRotate(Axis::Z, cubeMesh.rotation.z);
      */

      // pushing the vertices away by 5 units
      _transformed_vertex.z += 5;

      transformed_vertices[j] = _transformed_vertex;
    }
    
    // NOTE: Backface Culling
    Vec3D _vector_a = transformed_vertices[0]; /*   A   */
    Vec3D _vector_b = transformed_vertices[1]; /*  / \  */
    Vec3D _vector_c = transformed_vertices[2]; /* C - B */

    Vec3D vector_ab = _vector_b - _vector_a;
    Vec3D vector_ac = _vector_c - _vector_a;

    // Compute the face normal (using cross product)
    Vec3D normal = Vec3D::cross(vector_ab, vector_ac);
    Vec3D::normalize(normal);

    // Compute the camera ray
    Vec3D camera_ray = camera_position - _vector_a;

    // Compute camera_ray and normal vectors alignment using "dot product"
    float dot_normal_camera = Vec3D::dot(normal, camera_ray);

    if (dot_normal_camera < 0) {
      continue;
    }

    /* =================================================== */
    // NOTE: Loop all three vertices and perform "projection"
    Triangle projected_triangle;
    for (int j{0}; j < 3; j++) {
      // projecting the current transformed vertex
      Vec2D _projected_point = perspective_proj(transformed_vertices[j]);

      _projected_point.x += window->getWidth() / 2;
      _projected_point.y += window->getHeight() / 2;

      projected_triangle.points[j] = _projected_point;
    }
    /* =================================================== */

    triangles_to_render.push_back(projected_triangle);
  }
}
