#include "widgets/Widget.hpp"
#include <doctest/doctest.h>

namespace katze {
void Widget::resize(Gctx g, FRect &rect) {
  rect.w = g.clampWidth(0);
  rect.h = g.clampHeight(0);
}

void Widget::reposition(FVec2 position, FRect &rect) {
  rect.x = position.x;
  rect.y = position.y;
  repositionChildren(rect);
}

void Widget::repositionChildren([[maybe_unused]] FRect rect) {}
void Widget::view([[maybe_unused]] Dctx &d, [[maybe_unused]] FRect rect) {}

/*********/
/* Tests */
/*********/

TEST_CASE("[katze] Widget reposition") {
  Gctx g{nullptr, ThemeSizes{}, 960.0f, 640.0f, 1.0f};
  FRect rect{};
  Widget w{};
  w.resize(g, rect);

  SUBCASE("Reposition to (0, 0)") {
    const FVec2 pos{0, 0};
    w.reposition(pos, rect);
    CHECK(rect.x == pos.x);
    CHECK(rect.y == pos.y);
  }

  SUBCASE("Reposition to (120.5f, 120.5f)") {
    const FVec2 pos{120.5f, 120.5f};
    w.reposition(pos, rect);
    CHECK(rect.x == pos.x);
    CHECK(rect.y == pos.y);
  }
}
} // namespace katze
