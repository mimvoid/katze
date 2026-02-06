#ifndef KATZE_DRAW_HPP
#define KATZE_DRAW_HPP

/**
 * Primitive drawing functions for SDL.
 */

struct SDL_Renderer;
struct SDL_FRect;

namespace katze {
/**
 * Draw a line.
 *
 * @param rend Renderer to draw on.
 * @param x1 x-coordinate of the start point.
 * @param y1 y-coordinate of the start point.
 * @param x2 x-coordinate of the end point.
 * @param y2 y-coordinate of the end point.
 *
 * @return `true` on success, `false` on failure.
 */
bool drawLine(SDL_Renderer *rend, float x1, float y1, float x2, float y2);

/**
 * Draw a line with a set width.
 *
 * @param rend Renderer to draw on.
 * @param x1 x-coordinate of the start point.
 * @param y1 y-coordinate of the start point.
 * @param x2 x-coordinate of the end point.
 * @param y2 y-coordinate of the end point.
 * @param lineWidth Line width.
 *
 * @return `true` on success, `false` on failure.
 */
bool drawLine(
  SDL_Renderer *rend, float x1, float y1, float x2, float y2, float lineWidth
);

/**
 * Draw an unfilled rectangle.
 *
 * @param rend Renderer to draw on.
 * @param x x-coordinate of the top left corner.
 * @param y y-coordinate of the top left corner.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 *
 * @return `true` on success, `false` on failure.
 */
bool drawRect(SDL_Renderer *rend, float x, float y, float w, float h);

/**
 * Draw an unfilled rectangle with a set line width.
 *
 * @param rend Renderer to draw on.
 * @param x x-coordinate of the top left corner.
 * @param y y-coordinate of the top left corner.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 * @param lineWidth Line width.
 *
 * @return `true` on success, `false` on failure.
 */
bool drawRect(
  SDL_Renderer *rend, float x, float y, float w, float h, float lineWidth
);

/**
 * Draw an unfilled rectangle with a set line width.
 *
 * @param rend Renderer to draw on.
 * @param rect Rectangle to draw.
 * @return `true` on success, `false` on failure.
 */
bool drawRect(SDL_Renderer *rend, SDL_FRect rect);

/**
 * Draw an unfilled rectangle with a set line width.
 *
 * @param rend Renderer to draw on.
 * @param rect Rectangle to draw.
 * @param lineWidth Line width.
 * @return `true` on success, `false` on failure.
 */
bool drawRect(SDL_Renderer *rend, SDL_FRect rect, float lineWidth);

/**
 * Draw a filled rectangle with a set line width.
 *
 * @param rend Renderer to draw on.
 * @param x x-coordinate of the top left corner.
 * @param y y-coordinate of the top left corner.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 *
 * @return `true` on success, `false` on failure.
 */
bool drawRectFill(SDL_Renderer *rend, float x, float y, float w, float h);

/**
 * Draw a filled rectangle with a set line width.
 *
 * @param rend Renderer to draw on.
 * @param x x-coordinate of the top left corner.
 * @param y y-coordinate of the top left corner.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 * @param lineWidth Line width.
 *
 * @return `true` on success, `false` on failure.
 */
bool drawRectFill(
  SDL_Renderer *rend, float x, float y, float w, float h, float lineWidth
);

/**
 * Draw a filled rectangle with a set line width.
 *
 * @param rend Renderer to draw on.
 * @param rect Rectangle to draw.
 * @return `true` on success, `false` on failure.
 */
bool drawRectFill(SDL_Renderer *rend, SDL_FRect rect);

/**
 * Draw a filled rectangle with a set line width.
 *
 * @param rend Renderer to draw on.
 * @param rect Rectangle to draw.
 * @param lineWidth Line width.
 * @return `true` on success, `false` on failure.
 */
bool drawRectFill(SDL_Renderer *rend, SDL_FRect rect, float lineWidth);

/**
 * Draw an aliased (without anti-aliasing) unfilled ellipse.
 *
 * @param rend Renderer to draw on.
 * @param x x-coordinate of the center.
 * @param y y-coordinate of the center.
 * @param rx Horizontal radius.
 * @param ry Vertical radius.
 *
 * @return `true` on success, `false` on failure.
 */
bool aDrawEllipse(SDL_Renderer *rend, float x, float y, float rx, float ry);

/**
 * Draw a filled ellipse.
 *
 * @param rend Renderer to draw on.
 * @param x x-coordinate of the center.
 * @param y y-coordinate of the center.
 * @param rx Horizontal radius.
 * @param ry Vertical radius.
 *
 * @return `true` on success, `false` on failure.
 */
bool aDrawEllipseFill(SDL_Renderer *rend, float x, float y, float rx, float ry);

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
constexpr bool aDrawCircle(SDL_Renderer *rend, float x, float y, float r) {
  return aDrawEllipse(rend, x, y, r, r);
}

/**
 * Draw an aliased (without anti-aliasing) filled circle.
 *
 * @param rend Renderer to draw on.
 * @param x x-coordinate of the center.
 * @param y y-coordinate of the center.
 * @param r Radius of the circle.
 *
 * @return `true` on success, `false` on failure.
 */
constexpr bool aDrawCircleFill(SDL_Renderer *rend, float x, float y, float r) {
  return aDrawEllipseFill(rend, x, y, r, r);
}
} // namespace katze

#endif // !KATZE_DRAW_HPP
