#include "widgets/Checkbox.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Checkbox::resize(Gctx g, FRect &rect) {
  const float checkSize = g.font.size();
  rect.w = g.clampWidth(checkSize);
  rect.h = g.clampHeight(checkSize);
}

void Checkbox::view(Dctx &d, FRect rect) {
  if (updateState(d, rect)) {
    checked = !checked;
    d.messages.emplace_back(onCheck);
  }

  const StateColors &colors = d.colors();
  const SDL_FRect drawRect = d.scaledRect(rect);

  d.root.renderer().setDrawColor(colors.base);
  SDL_RenderFillRect(d.root.sdlRenderer(), &drawRect);

  const bool drawBorder = d.root.theme.borderWidth != 0;
  if (drawBorder || checked) {
    d.root.renderer().setDrawColor(colors.border);

    if (drawBorder) {
      SDL_RenderRect(d.root.sdlRenderer(), &drawRect);
    }
    if (checked) {
      const float gap = d.root.theme.borderWidth * 2 * d.scale;
      const SDL_FRect checkRect{
        drawRect.x + gap,
        drawRect.y + gap,
        drawRect.w - (2 * gap),
        drawRect.h - (2 * gap)
      };
      SDL_RenderFillRect(d.root.sdlRenderer(), &checkRect);
    }
  }
}
} // namespace katze
