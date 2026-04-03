#ifndef KATZE_WIDGETS_CAPSULE_HPP
#define KATZE_WIDGETS_CAPSULE_HPP

#include <memory>
#include <utility>
#include "Widget.hpp"

namespace katze {
/**
 * Bin that contains a single child widget.
 */
struct Capsule : Widget {
  std::shared_ptr<Widget> child{};
  FRect childRect{};

  Capsule() = default;

  template <class T, typename = ifIsWidget<T>>
  Capsule(std::shared_ptr<T> child) : child(child) {}

  template <class T, typename = ifIsWidget<T>>
  Capsule(T &&child) : child(std::make_shared<T>(std::forward<T>(child))) {}

  void resize(Gctx g, FRect &rect) override;
  void repositionChildren(FRect rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_CAPSULE_HPP
