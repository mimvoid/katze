#include "widgets/Widget.hpp"

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
}
