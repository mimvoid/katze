#ifndef KATZE_THEME_HPP
#define KATZE_THEME_HPP

#include "Font.hpp"
#include "core/State.hpp"

namespace katze {
/**
 * Color theme settings.
 */
struct ThemeColors {
  StateColors normal{{242, 160, 164}, {250, 223, 200}, {39, 39, 42}};
  StateColors disabled{{217, 141, 150}, {235, 192, 180}, {57, 57, 60}};
  StateColors focus{{248, 149, 155}, {250, 214, 190}, {39, 39, 42}};
  StateColors active{{54, 47, 64}, {213, 132, 134}, {252, 229, 233}};

  constexpr const StateColors &forState(State state) const {
    switch (state) {
    case State::DISABLED: return disabled;
    case State::FOCUS:    return focus;
    case State::ACTIVE:   return active;
    default:              return normal;
    }
  }
};

/**
 * Theme settings that may resize widgets.
 */
struct ThemeSizes {
  // Default font for a label, which should be resized by the window display scale.
  Font font{};

  uint8_t border{2};
  uint8_t iconScale{1};
};

/**
 * Settings to theme katze widgets.
 */
struct Theme {
  ThemeColors colors{};
  ThemeSizes sizes{};
};
} // namespace katze

#endif // !KATZE_THEME_HPP
