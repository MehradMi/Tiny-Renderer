#ifndef COLOR_BUFFER_TEXTURE_H
#define COLOR_BUFFER_TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <memory>

struct SDL_TextureDeleter {
  void operator()(SDL_Texture* texture) const {
    if (texture) {
      SDL_DestroyTexture(texture);
    }
  }
};

class ColorBufferTexture {
private:
  int           m_width;
  int           m_height;
  int           m_access;
  uint32_t      m_format;
  std::unique_ptr<SDL_Texture, SDL_TextureDeleter> m_texture;
  SDL_Renderer *m_rendering_context;

public:
  ColorBufferTexture() = delete;
  ColorBufferTexture(SDL_Renderer* r, int w, int h, int a, uint32_t f);
  ColorBufferTexture(const ColorBufferTexture&) = delete;
  ColorBufferTexture& operator=(const ColorBufferTexture&) = delete;
  ColorBufferTexture(ColorBufferTexture&&) noexcept;
  ColorBufferTexture& operator=(ColorBufferTexture&&) noexcept;
  ~ColorBufferTexture() = default;

  SDL_Texture* getTexture() const { return m_texture.get(); }
};

#endif
