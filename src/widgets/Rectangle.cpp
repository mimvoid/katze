#include "widgets/Rectangle.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "Dctx.hpp"

namespace katze {
void Rectangle::resize(Gctx g, FRect &rect) {
  float w = maxSize.x;
  float h = maxSize.y;

  if (bordered) {
    w += 2 * g.sizes.border;
    h += 2 * g.sizes.border;
  }

  rect.w = g.clampWidth(w);
  rect.h = g.clampHeight(h);
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
    rend.drawRect(drawRect, d.root.theme.sizes.border * d.scale);
  }
}
} // namespace katze
