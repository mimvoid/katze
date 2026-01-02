#include "Renderer.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Window.hpp"
#include "draw.hpp"

namespace katze {
Renderer::Renderer(Window &window)
  : window(window),
    m_data(SDL_GetRenderer(window.data)),
    m_textEngine(TTF_CreateRendererTextEngine(m_data)) {}

void Renderer::destroy() {
  TTF_DestroyRendererTextEngine(m_textEngine);
  SDL_DestroyRenderer(m_data);
}

void Renderer::setData(SDL_Renderer *renderer) {
  m_data = renderer;
  m_textEngine = TTF_CreateRendererTextEngine(renderer);
}

bool Renderer::clear() {
  SDL_SetRenderDrawColor(
    m_data, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255
  );
  return SDL_RenderClear(m_data);
}

bool Renderer::present() { return SDL_RenderPresent(m_data); }

bool Renderer::setDrawColor(Rgb rgb) {
  return SDL_SetRenderDrawColor(m_data, rgb.r, rgb.g, rgb.b, 255);
}

bool Renderer::setDrawColor(Rgba rgba) {
  return SDL_SetRenderDrawColor(m_data, rgba.r, rgba.g, rgba.b, rgba.a);
}

bool Renderer::drawLine(
  float x1, float y1, float x2, float y2, float lineWidth
) {
  return katze::drawLine(m_data, x1, y1, x2, y2, lineWidth);
}

bool Renderer::drawRect(float x, float y, float w, float h, float lineWidth) {
  return katze::drawRect(m_data, x, y, w, h, lineWidth);
}

bool Renderer::drawRectFill(
  float x, float y, float w, float h, float lineWidth
) {
  return katze::drawRectFill(m_data, x, y, w, h, lineWidth);
}

bool Renderer::aDrawEllipse(float x, float y, float rx, float ry) {
  return katze::aDrawEllipse(m_data, x, y, rx, ry);
}

bool Renderer::aDrawEllipseFill(float x, float y, float rx, float ry) {
  return katze::aDrawEllipseFill(m_data, x, y, rx, ry);
}
} // namespace katze
