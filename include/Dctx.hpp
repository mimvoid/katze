#ifndef KATZE_DCTX_HPP
#define KATZE_DCTX_HPP

#include <vector>
#include "Root.hpp"
#include "core/State.hpp"
#include "input/Cursor.hpp"
#include "input/mouse.hpp"

struct SDL_Renderer;
struct SDL_FRect;

namespace katze {
/**
 * A drawing context that provides theme settings and stores a widget state
 * that can be passed to children.
 */
struct Dctx {
  struct MouseInfo {
    bool valid{false}; // Whether the info applies to this widget tree.
    ButtonState leftButton{ButtonState::UP};
    float x{0.0f};
    float y{0.0f};
  };

  Root &root;
  float scale{1.0f}; // Display scale of the root's renderer window.

  MouseInfo mouse{};
  std::vector<uint32_t> messages{};

  State state{State::NORMAL};
  Cursor cursor{Cursor::DEFAULT};

  constexpr const StateColors &colors() const {
    return root.theme.colors.forState(state);
  }

  SDL_FRect scaledRect(FRect rect) const;
};
} // namespace katze

#endif // !KATZE_CTX_DCTX_HPP
