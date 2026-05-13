#include "ColorBufferTexture.h"
#include <SDL2/SDL_render.h>

ColorBufferTexture::ColorBufferTexture(SDL_Renderer *r, int w, int h, int a, uint32_t f):
  m_width(w),
  m_height(h),
  m_access(a),
  m_format(f),
  m_cbt(nullptr),
  m_rendering_context(r)
{
  if (m_width && m_height) {
    // TODO: add error handling
    m_cbt = SDL_CreateTexture(m_rendering_context, m_format, m_access, m_width, m_height);
  }
}

ColorBufferTexture::ColorBufferTexture(ColorBufferTexture&& other) noexcept:
  m_width(other.m_width),
  m_height(other.m_height),
  m_access(other.m_access),
  m_format(other.m_format),
  m_cbt(other.m_cbt),
  m_rendering_context(other.m_rendering_context)
{
  // Nullify "other"
  other.m_width  = 0;
  other.m_height = 0;
  other.m_height = 0;
  other.m_access = 0;
  other.m_format = 0;
  other.m_cbt    = nullptr;
  other.m_rendering_context = nullptr;
}

ColorBufferTexture& ColorBufferTexture::operator=(ColorBufferTexture&& other) noexcept {
  // Self-Assignment Check
  if (this == &other)
    return *this;

  // Clean Up Current Existing Resources Before Replacing Them
  if (m_cbt)
    SDL_DestroyTexture(m_cbt);

  // Steal Resources
  m_width  = other.m_width;
  m_height = other.m_height;
  m_access = other.m_access;
  m_format = other.m_format;
  m_cbt    = other.m_cbt;
  m_rendering_context = other.m_rendering_context;

  // Nullify "other"
  other.m_width  = 0;
  other.m_height = 0;
  other.m_access = 0;
  other.m_format = 0;
  other.m_cbt    = nullptr;
  other.m_rendering_context = nullptr;

  return *this;
}

ColorBufferTexture::~ColorBufferTexture() {
  if (m_cbt) {
    SDL_DestroyTexture(m_cbt);
    m_cbt = nullptr;
  }
}
