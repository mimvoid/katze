#include "ctx/Dctx.hpp"
#include <SDL3/SDL_rect.h>

namespace katze {
SDL_FRect Dctx::scaledRect(FRect rect) const {
  return SDL_FRect{
    rect.x * scale, rect.y * scale, rect.w * scale, rect.h * scale
  };
}
} // namespace katze
