#include "Root.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Dctx.hpp"
#include "Window.hpp"

namespace katze {
Root::Root(Renderer renderer, Theme theme)
  : theme(theme),
    mRenderer(renderer),
    mTextEngine(TTF_CreateRendererTextEngine(renderer.data)) {}

void Root::destroy() {
  focused = nullptr;
  child.reset();

  TTF_DestroyRendererTextEngine(mTextEngine);
  mTextEngine = nullptr;
}

void Root::setFont(Font font) {
  const float scale = mRenderer.window().displayScale();
  if (scale > 0.0f) {
    font.setSize(font.size() * scale);
  }
  theme.sizes.font = font;
}

void Root::setFontUnscaled(Font font) { theme.sizes.font = font; }

void Root::layout() {
  std::optional<IVec2> size = mRenderer.window().size();
  if (size.has_value()) {
    layout(size->x, size->y);
  }
}

void Root::layout(float width, float height) {
  if (!child) return;

  const Gctx g{
    mTextEngine, theme.sizes, width, height, mRenderer.window().displayScale()
  };
  child->resize(g, childRect);

  // Once the child's resized, we can know how to align it.
  const float offsetX = offset(g.w, childRect.w, align.x);
  const float offsetY = offset(g.h, childRect.h, align.y);

  child->reposition(Vec2{offsetX, offsetY}, childRect);
}

std::vector<uint32_t> Root::view() {
  if (!child) return {};

  Dctx d{*this, mRenderer.window().displayScale()};

  // Set the mouse info for this window, if any.
  if (mRenderer.window().focused()) {
    const MouseState mouse = mouseState();
    d.mouse = Dctx::MouseInfo{true, mouse.leftButton, mouse.x, mouse.y};
  }

  child->view(d, childRect);
  setCursor(d.cursor);

  return d.messages;
}
} // namespace katze
