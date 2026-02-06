#include "widgets/Icon.hpp"
#include <SDL3/SDL_render.h>
#include "ctx/Dctx.hpp"

namespace katze {
void Icon::resize(Gctx g, FRect &rect) {
  const float iconSize = m_scale * KATZE_ICON_SIZE;
  rect.w = g.clampWidth(iconSize);
  rect.h = g.clampHeight(iconSize);
}

void Icon::view(Dctx &d, FRect rect) {
  d.root.renderer().setDrawColor(d.colors().text);
  drawIcon(
    d.root.sdlRenderer(),
    bits,
    rect.x * d.scale,
    rect.y * d.scale,
    m_scale * d.root.theme.iconSize * d.scale
  );
}
} // namespace katze
