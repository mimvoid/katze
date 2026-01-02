#ifndef KATZE_RENDERER_HPP
#define KATZE_RENDERER_HPP

#include "core/Rgba.hpp"

struct SDL_Renderer;
struct TTF_TextEngine;

namespace katze {
struct Window;

struct Renderer {
  Window &window;
  Rgb backgroundColor{};

  Renderer(Window &window);

  void destroy();

  constexpr SDL_Renderer *data() const { return m_data; }
  void setData(SDL_Renderer *data);

  constexpr TTF_TextEngine *textEngine() const { return m_textEngine; }

  bool clear();
  bool present();

  bool setDrawColor(Rgb rgb);
  bool setDrawColor(Rgba rgba);

  /**
   * Draw a line with a set width.
   *
   * @param x1 x-coordinate of the start point.
   * @param y1 y-coordinate of the start point.
   * @param x2 x-coordinate of the end point.
   * @param y2 y-coordinate of the end point.
   * @param lineWidth Line width.
   *
   * @return `true` on success, `false` on failure.
   */
  bool drawLine(float x1, float y1, float x2, float y2, float lineWidth = 1.0f);

  /**
   * Draw an unfilled rectangle with a set line width.
   *
   * @param x x-coordinate of the top left corner.
   * @param y y-coordinate of the top left corner.
   * @param w Width of the rectangle.
   * @param h Height of the rectangle.
   * @param lineWidth Line width.
   *
   * @return `true` on success, `false` on failure.
   */
  bool drawRect(float x, float y, float w, float h, float lineWidth = 1.0f);

  /**
   * Draw a filled rectangle with a set line width.
   *
   * @param x x-coordinate of the top left corner.
   * @param y y-coordinate of the top left corner.
   * @param w Width of the rectangle.
   * @param h Height of the rectangle.
   * @param lineWidth Line width.
   *
   * @return `true` on success, `false` on failure.
   */
  bool drawRectFill(float x, float y, float w, float h, float lineWidth = 1.0f);

  /**
   * Draw an aliased (without anti-aliasing) unfilled ellipse.
   *
   * @param x x-coordinate of the center.
   * @param y y-coordinate of the center.
   * @param rx Horizontal radius.
   * @param ry Vertical radius.
   *
   * @return `true` on success, `false` on failure.
   */
  bool aDrawEllipse(float x, float y, float rx, float ry);

  /**
   * Draw a filled ellipse.
   *
   * @param x x-coordinate of the center.
   * @param y y-coordinate of the center.
   * @param rx Horizontal radius.
   * @param ry Vertical radius.
   *
   * @return `true` on success, `false` on failure.
   */
  bool aDrawEllipseFill(float x, float y, float rx, float ry);

  /**
   * Draw an aliased (without anti-aliasing) unfilled circle.
   *
   * @param rend Renderer to draw on.
   * @param x x-coordinate of the center.
   * @param y y-coordinate of the center.
   * @param r Radius of the circle.
   *
   * @return `true` on success, `false` on failure.
   */
  constexpr bool aDrawCircle(float x, float y, float r) {
    return aDrawEllipse(x, y, r, r);
  }

  /**
   * Draw an aliased (without anti-aliasing) filled circle.
   *
   * @param x x-coordinate of the center.
   * @param y y-coordinate of the center.
   * @param r Radius of the circle.
   *
   * @return `true` on success, `false` on failure.
   */
  constexpr bool aDrawCircleFill(float x, float y, float r) {
    return aDrawEllipseFill(x, y, r, r);
  }

private:
  SDL_Renderer *m_data{nullptr};
  TTF_TextEngine *m_textEngine{nullptr};
};
} // namespace katze

#endif // !KATZE_RENDERER_HPP
