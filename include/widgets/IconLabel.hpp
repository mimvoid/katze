#ifndef KATZE_WIDGETS_ICONLABEL_HPP
#define KATZE_WIDGETS_ICONLABEL_HPP

#include "Icon.hpp"
#include "Label.hpp"
#include "Widget.hpp"

namespace katze {
struct IconLabel : Widget {
  Label label{};
  Icon icon{};

  FRect labelRect{};
  FRect iconRect{};

  int spacing{0};

  IconLabel() = default;

  IconLabel(Icon &&icon, Label &&label, int spacing = 0)
    : label(std::forward<Label>(label)),
      icon(std::forward<Icon>(icon)),
      spacing(spacing) {}

  IconLabel(const IconBits &bits, const char *text = "", int spacing = 0)
    : label(text), icon(bits), spacing(spacing) {}

  void resize(Gctx g, FRect &rect) override;
  void repositionChildren(FRect rect) override;
  void view(Dctx &d, FRect rect) override;
};
} // namespace katze

#endif // !KATZE_WIDGETS_ICONLABEL_HPP
