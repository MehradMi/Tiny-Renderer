#ifndef COLOR_BUFFER_TEXTURE_H
#define COLOR_BUFFER_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>

class ColorBufferTexture {
private:
  int           m_width;
  int           m_height;
  int           m_access;
  uint32_t      m_format;
  SDL_Texture  *m_cbt;
  SDL_Renderer *m_rendering_context;

public:
  ColorBufferTexture(SDL_Renderer* r, int w, int h, int a, uint32_t f);
  ColorBufferTexture(const ColorBufferTexture&) = delete;
  ColorBufferTexture& operator=(const ColorBufferTexture&) = delete;
  ColorBufferTexture(ColorBufferTexture&&) noexcept;
  ColorBufferTexture& operator=(ColorBufferTexture&&) noexcept;
  ~ColorBufferTexture();

  SDL_Texture* getTexture() { return m_cbt; }
};

#endif
