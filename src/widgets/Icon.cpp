#include "widgets/Icon.hpp"
#include <SDL3/SDL_render.h>
#include <doctest/doctest.h>
#include "Dctx.hpp"

namespace katze {
void Icon::resize(Gctx g, FRect &rect) {
  const float iconSize = m_scale * g.sizes.iconScale * KATZE_ICON_SIZE;
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
    m_scale * d.root.theme.sizes.iconScale * d.scale
  );
}

/*********/
/* Tests */
/*********/

TEST_CASE("[katze] Icon initial fields") {
  IconBits emptyIcon{};

  const Icon withBits{emptyIcon};
  REQUIRE(withBits.bits == emptyIcon);
  REQUIRE(withBits.scale() == 1);

  const Icon withSize{emptyIcon, 2};
  REQUIRE(withSize.bits == emptyIcon);
  REQUIRE(withSize.scale() == 2);
}

TEST_CASE("[katze] Set Icon size, within bounds") {
  Icon icon{};
  icon.setScale(2);
  CHECK(icon.scale() == 2);
}

TEST_CASE("[katze] Try setting Icon size of 0") {
  Icon icon{};
  icon.setScale(0);
  CHECK(icon.scale() == 1);
}

TEST_CASE("[katze] Measure Icon size") {
  const uint8_t iconScale = 1;

  Icon icon{};
  FRect rect{};
  Gctx g{nullptr, ThemeSizes{Font{}, 1, iconScale}, 960.0f, 640.0f, 1.0f};
  icon.resize(g, rect);

  const int iconSize = icon.scale() * KATZE_ICON_SIZE;
  CHECK(rect.w == iconSize);
  CHECK(rect.h == iconSize);
}
} // namespace katze
