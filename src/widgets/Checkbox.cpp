#include "widgets/Checkbox.hpp"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include "Dctx.hpp"

namespace katze {
void Checkbox::resize(Gctx g, FRect &rect) {
  const float checkSize = g.sizes.font.size() + (2 * g.sizes.border);
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

  Renderer rend = d.root.renderer();
  rend.setDrawColor(colors.base);
  rend.drawRectFill(drawRect);

  const float borderWidth = d.root.theme.sizes.border * d.scale;
  if (borderWidth != 0) {
    rend.setDrawColor(colors.border);
    rend.drawRect(drawRect, borderWidth);

    if (checked) {
      const float gap = borderWidth * 2;
      rend.drawRectFill({
        drawRect.x + gap,
        drawRect.y + gap,
        drawRect.w - (2 * gap),
        drawRect.h - (2 * gap)
      });
    }
  } else if (checked) {
    rend.setDrawColor(colors.border);
    rend.drawRectFill(drawRect);
  }
}
} // namespace katze
