#include "bins/Button.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include "Dctx.hpp"

namespace katze {
void Clickable::view(Dctx &d, FRect rect) {
  if (updateState(d, rect)) {
    d.messages.emplace_back(onClick);
  }
  if (child) {
    child->view(d, childRect);
  }
}

void Button::resize(Gctx g, FRect &rect) {
  const float offset = padding + g.sizes.border;

  if (child) {
    Gctx gCopy = g;
    gCopy.shrink(FEdges(offset));
    child->resize(gCopy, childRect);
  } else {
    childRect.w = 0;
    childRect.h = 0;
  }

  rect.w = g.clampWidth(childRect.w + (2.0f * offset));
  rect.h = g.clampHeight(childRect.h + (2.0f * offset));
}

void Button::repositionChildren(FRect rect) {
  if (child) {
    child->reposition({rect.x + padding, rect.y + padding}, childRect);
  }
}

void Button::view(Dctx &d, FRect rect) {
  if (updateState(d, rect)) {
    d.messages.emplace_back(onClick);
  }

  SDL_FRect drawRect = d.scaledRect(rect);
  StateColors colors = d.colors();
  Renderer rend = d.root.renderer();

  rend.setDrawColor(colors.base);
  rend.drawRectFill(drawRect);

  if (d.root.theme.sizes.border != 0) {
    rend.setDrawColor(colors.border);
    rend.drawRect(drawRect, d.root.theme.sizes.border * d.scale);
  }

  if (child) {
    child->view(d, childRect);
  }
}
} // namespace katze
