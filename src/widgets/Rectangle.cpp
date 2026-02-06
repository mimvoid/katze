#include "widgets/Rectangle.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Rectangle::resize(Gctx g, FRect &rect) {
  rect.w = g.clampWidth(maxSize.x);
  rect.h = g.clampHeight(maxSize.y);
}

void Rectangle::view(Dctx &d, FRect rect) {
  if (!filled && !bordered) return;

  SDL_FRect drawRect = d.scaledRect(rect);
  StateColors colors = d.colors();
  Renderer rend = d.root.renderer();

  if (filled) {
    rend.setDrawColor(colors.base);
    rend.drawRectFill(drawRect);
  }

  if (bordered) {
    rend.setDrawColor(colors.border);
    rend.drawRect(drawRect, d.root.theme.borderWidth * d.scale);
  }
}
} // namespace katze
