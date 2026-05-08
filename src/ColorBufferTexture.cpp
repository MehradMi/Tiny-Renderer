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

ColorBufferTexture::~ColorBufferTexture() {
  if (m_cbt) {
    SDL_DestroyTexture(m_cbt);
    m_cbt = nullptr;
  }
}
