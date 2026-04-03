#ifndef KATZE_ROOT_HPP
#define KATZE_ROOT_HPP

#include <memory>
#include <vector>
#include "Renderer.hpp"
#include "Theme.hpp"
#include "core/Align.hpp"
#include "widgets/Reactive.hpp"
#include "widgets/Widget.hpp"

struct TTF_TextEngine;

namespace katze {
/**
 * Entry-point to a katze widget tree.
 */
struct Root {
  Theme theme{};
  AlignVec2 align{Align::CENTER};

  std::shared_ptr<Widget> child{};
  FRect childRect{};

  // Currently focused reactive widget, such as being hovered over or pressed.
  Reactive *focused{};

  Root(Renderer renderer, Theme theme = {});

  /**
   * Free the text engine and any widgets.
   */
  void destroy();

  constexpr Renderer renderer() const { return mRenderer; }
  constexpr SDL_Renderer *sdlRenderer() const { return mRenderer.data; }
  constexpr TTF_TextEngine *textEngine() const { return mTextEngine; }

  constexpr Font font() const { return theme.sizes.font; }

  /**
   * Set the default font and scale its size according to the renderer window's
   * display scale.
   */
  void setFont(Font font);

  /**
   * Set the default font without changing its size.
   */
  void setFontUnscaled(Font font);

  /**
   * Find the size of the window and resize and reposition the widgets.
   */
  void layout();

  /**
   * Given a known window size, resize and reposition the widgets in the tree.
   */
  void layout(float width, float height);

  /**
   * Draw the widgets and collect messages.
   */
  std::vector<uint32_t> view();

private:
  Renderer mRenderer;
  TTF_TextEngine *mTextEngine{nullptr};
};
} // namespace katze

#endif // !KATZE_ROOT_HPP
