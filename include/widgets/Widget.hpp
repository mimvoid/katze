#ifndef KATZE_WIDGETS_WIDGET_HPP
#define KATZE_WIDGETS_WIDGET_HPP

#include <type_traits>
#include "../Gctx.hpp"
#include "../core/Rect.hpp"
#include "../core/Vec2.hpp"

namespace katze {
struct Dctx;

/**
 * Variable data for a widget.
 */
struct Widget {
  virtual ~Widget() = default;

  void reposition(FVec2 position, FRect &rect);
  virtual void resize(Gctx g, FRect &rect);
  virtual void view(Dctx &d, FRect rect);

protected:
  virtual void repositionChildren(FRect rect);
};

template <class T>
using ifIsWidget = std::enable_if_t<std::is_base_of_v<Widget, T>>;
} // namespace katze

#endif // !KATZE_WIDGETS_WIDGET_HPP
