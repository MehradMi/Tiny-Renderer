#include "color_buffer.h"
#include "renderer.h"
#include <SDL2/SDL_render.h>
#include <new>

ColorBuffer::ColorBuffer(): 
  m_buffer(nullptr),
  m_buffer_texture(nullptr),
  m_width(500),
  m_height(500)
{
}

ColorBuffer::ColorBuffer(int buffer_width, int buffer_height):
  m_buffer(nullptr),
  m_buffer_texture(nullptr)
{
  m_width  = buffer_width;
  m_height = buffer_height;
}

void ColorBuffer::create_buffer_texture(Renderer *renderer ,uint32_t tex_format, int access, int tex_width, int tex_height) {
  m_buffer_texture = SDL_CreateTexture(renderer->get_sdl_renderer(), tex_format, access, tex_format, tex_height);
}

void ColorBuffer::create_buffer() {
  m_buffer = new (std::nothrow) pixel[m_width * m_height];
}

void ColorBuffer::clear_buffer(hex_color color) {
  for (auto y{0}; y < m_height; y++) {
    for (auto x{0}; x < m_width; x++) {
      paint_pixel(x, y, color);
    }
  }
}

void ColorBuffer::paint_pixel(int x, int y, hex_color color) {
  m_buffer[(m_width * y) + x] = color;
} 

void ColorBuffer::render(Renderer *renderer) {
  SDL_UpdateTexture(m_buffer_texture, nullptr, m_buffer, m_width * sizeof(pixel));
  SDL_RenderCopy(renderer->get_sdl_renderer(), m_buffer_texture, nullptr, nullptr);
}
