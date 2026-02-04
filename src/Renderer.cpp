#include "Renderer.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.hpp"
#include "draw.hpp"

namespace katze {
Renderer::Renderer(SDL_Renderer *renderer) : data(renderer) {}
Renderer::Renderer(Window window) : data(SDL_GetRenderer(window.data)) {}

void Renderer::destroy() { SDL_DestroyRenderer(data); }

Window Renderer::window() const { return Window{SDL_GetRenderWindow(data)}; }

bool Renderer::clear() {
  SDL_SetRenderDrawColor(
    data, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255
  );
  return SDL_RenderClear(data);
}

bool Renderer::present() { return SDL_RenderPresent(data); }

bool Renderer::setDrawColor(Rgb rgb) {
  return SDL_SetRenderDrawColor(data, rgb.r, rgb.g, rgb.b, 255);
}

bool Renderer::setDrawColor(Rgba rgba) {
  return SDL_SetRenderDrawColor(data, rgba.r, rgba.g, rgba.b, rgba.a);
}

bool Renderer::drawLine(
  float x1, float y1, float x2, float y2, float lineWidth
) {
  return katze::drawLine(data, x1, y1, x2, y2, lineWidth);
}

bool Renderer::drawRect(float x, float y, float w, float h, float lineWidth) {
  return katze::drawRect(data, x, y, w, h, lineWidth);
}

bool Renderer::drawRectFill(
  float x, float y, float w, float h, float lineWidth
) {
  return katze::drawRectFill(data, x, y, w, h, lineWidth);
}

bool Renderer::aDrawEllipse(float x, float y, float rx, float ry) {
  return katze::aDrawEllipse(data, x, y, rx, ry);
}

bool Renderer::aDrawEllipseFill(float x, float y, float rx, float ry) {
  return katze::aDrawEllipseFill(data, x, y, rx, ry);
}
} // namespace katze
