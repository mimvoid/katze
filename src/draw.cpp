#include "draw.hpp"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <cmath>
#include <vector>

namespace katze {
/*---------*/
/* Helpers */
/*---------*/

struct ShorthandResult {
  bool shorthanded : 1; // Whether a shorthanded operation was executed
  bool success : 1;     // Whether the shorthanded execution was successful
};

int approxCirclePointCount(float rad) { return rad * 8 * 35 / 49; }
int upperMultipleOfEight(int value) { return (value + 7) & -8; }

void appendQuadrantPoints(
  std::vector<SDL_FPoint> &vec, float x, float y, float offsetX, float offsetY
) {
  vec.insert(
    vec.end(),
    {
      {x + offsetX, y + offsetY},
      {x - offsetX, y + offsetY},
      {x - offsetX, y - offsetY},
      {x + offsetX, y - offsetY},
    }
  );
}

/**
 * Calculates the degrees required to rotate a horizontal line clockwise if
 * anchored to the first point (x1, y1).
 */
double clockwiseRotationDegrees(float x1, float y1, float x2, float y2) {
  if (y1 == y2) {
    return (x2 >= x1) ? 0.0 : 180.0;
  }
  if (x1 == x2) {
    return (y2 <= y1) ? 90.0 : 270.0;
  }

  const double counterClockwiseDeg =
    atan((y1 - y2) / std::abs((double)x2 - x1)) * 180.0 / M_PI;

  if (x2 < x1) {
    return 180.0 + counterClockwiseDeg;
  }
  return 360.0 - counterClockwiseDeg;
}

ShorthandResult
aEllipseShorthand(SDL_Renderer *rend, float x, float y, float rx, float ry) {
  if (rend == nullptr || rx < 0.0f || ry < 0.0f) {
    return {true, false}; // Invalid parameters
  }

  if (rx <= 0.5f) {
    if (ry <= 0.5f) {
      // Ellipse is small enough to just be a point
      return {true, SDL_RenderPoint(rend, x, y)};
    }
    // Draw as a vertical line
    return {true, SDL_RenderLine(rend, x, y - ry, x, y + ry)};
  }
  if (ry <= 0.5f) {
    // Draw as a horizontal line
    return {true, SDL_RenderLine(rend, x - rx, y, x + rx, y)};
  }

  return {false, false};
}

/**
 * Draw using a Bresenham type algorithm.
 * See: Kennedy, John. "A Fast Bresenham Type Algorithm For Drawing Ellipses"
 */
std::vector<SDL_FPoint> aEllipsePoints(float x, float y, float rx, float ry) {
  std::vector<SDL_FPoint> points{};
  points.reserve(
    upperMultipleOfEight(approxCirclePointCount((rx + ry) / 2.0f))
  );

  // Diameters
  const float xd = rx * 2.0f;
  const float yd = ry * 2.0f;

  float offsetX = rx;
  float offsetY = 0.0f;

  float dx = ry * ry * (1.0f - xd);
  float dy = rx * rx;
  float error = 0.0f;

  float stopX = yd * ry * rx;
  float stopY = 0.0f;

  while (stopX >= stopY) {
    appendQuadrantPoints(points, x, y, offsetX, offsetY);

    offsetY++;
    stopY += xd * rx;
    error += dy;
    dy += xd * rx;

    if (2 * error + dx > 0.0f) {
      offsetX--;
      stopX -= yd * ry;
      error += dx;
      dx += yd * ry;
    }
  }

  offsetX = 0.0f;
  offsetY = ry;

  dx = ry * ry;
  dy = rx * rx * (1.0f - yd);
  error = 0.0f;

  stopX = 0.0f;
  stopY = xd * rx * ry;

  while (stopX <= stopY) {
    appendQuadrantPoints(points, x, y, offsetX, offsetY);

    offsetX++;
    stopX += yd * ry;
    error += dx;
    dx += yd * ry;

    if (2 * error + dy > 0) {
      offsetY--;
      stopY -= xd * rx;
      error += dy;
      dy += xd * rx;
    }
  }

  return points;
}

/*-------------*/
/* Definitions */
/*-------------*/

bool drawLine(SDL_Renderer *rend, float x1, float y1, float x2, float y2) {
  return SDL_RenderLine(rend, x1, y1, x2, y2);
}

bool drawLine(
  SDL_Renderer *rend, float x1, float y1, float x2, float y2, float lineWidth
) {
  if (rend == nullptr || lineWidth < 0.0f) {
    return false;
  }
  if (lineWidth <= 1.0f) {
    return SDL_RenderLine(rend, x1, y1, x2, y2);
  }

  const float halfWidth = lineWidth / 2.0f;

  if (x1 == x2 || y1 == y2) {
    // Draw a straight rectangle.
    const SDL_FRect rect{
      x1 - halfWidth, y1 - halfWidth, x2 - x1 + lineWidth, y2 - y1 + lineWidth
    };
    return SDL_RenderFillRect(rend, &rect);
  }

  // Draw a rotated rectangle using a rotated texture.

  SDL_Color color{0, 0, 0, 255};
  if (!SDL_GetRenderDrawColor(rend, &color.r, &color.g, &color.b, &color.a)) {
    return false;
  }

  bool result = false;

  const float dist = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
  SDL_Surface *surface =
    SDL_CreateSurface(dist + lineWidth, lineWidth, SDL_PIXELFORMAT_RGB24);

  if (surface) {
    const Uint32 rgb = SDL_MapRGB(
      SDL_GetPixelFormatDetails(surface->format),
      nullptr,
      color.r,
      color.g,
      color.b
    );

    if (SDL_FillSurfaceRect(surface, nullptr, rgb)) {
      SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);

      if (texture) {
        const SDL_FRect dst{
          x1 - halfWidth, y1 - halfWidth, dist + lineWidth, lineWidth
        };

        const SDL_FPoint anchor{halfWidth, halfWidth};
        const double deg = clockwiseRotationDegrees(x1, y1, x2, y2);

        result = SDL_SetTextureAlphaMod(texture, color.a);
        result &= SDL_RenderTextureRotated(
          rend, texture, nullptr, &dst, deg, &anchor, SDL_FLIP_NONE
        );
      }

      SDL_DestroyTexture(texture);
    }
  }

  SDL_DestroySurface(surface);
  return result;
}

bool drawRect(SDL_Renderer *rend, float x, float y, float w, float h) {
  SDL_FRect rect{x, y, w, h};
  return SDL_RenderRect(rend, &rect);
}

bool drawRect(
  SDL_Renderer *rend, float x, float y, float w, float h, float lineWidth
) {
  return drawRect(rend, SDL_FRect{x, y, w, h}, lineWidth);
}

bool drawRect(SDL_Renderer *rend, SDL_FRect rect) {
  return SDL_RenderRect(rend, &rect);
}

bool drawRect(SDL_Renderer *rend, SDL_FRect rect, float lineWidth) {
  if (rend == nullptr || lineWidth < 0.0f) {
    return false; // Invalid parameters.
  }

  if (lineWidth <= 1.0f) {
    // Draw with a line width of 1.
    return SDL_RenderRect(rend, &rect);
  }

  const float halfWidth = lineWidth / 2.0f;
  const float x0 = rect.x - halfWidth;
  const float y0 = rect.y - halfWidth;

  // Create thick lines using filled rectangles.
  const SDL_FRect lines[4]{
    {x0, y0, rect.w + lineWidth, lineWidth},          // Top line
    {x0, y0 + rect.h, rect.w + lineWidth, lineWidth}, // Bottom line
    {x0, y0, lineWidth, rect.h + lineWidth},          // Left line
    {x0 + rect.w, y0, lineWidth, rect.h + lineWidth}, // Right line
  };

  return SDL_RenderFillRects(rend, lines, 4);
}

bool drawRectFill(SDL_Renderer *rend, float x, float y, float w, float h) {
  SDL_FRect rect{x, y, w, h};
  return SDL_RenderFillRect(rend, &rect);
}

bool drawRectFill(
  SDL_Renderer *rend, float x, float y, float w, float h, float lineWidth
) {
  return drawRect(rend, SDL_FRect{x, y, w, h}, lineWidth);
}

bool drawRectFill(SDL_Renderer *rend, SDL_FRect rect) {
  return SDL_RenderFillRect(rend, &rect);
}

bool drawRectFill(SDL_Renderer *rend, SDL_FRect rect, float lineWidth) {
  if (rend == nullptr || lineWidth < 0.0f) {
    return false;
  }

  if (lineWidth <= 1.0f) {
    // Draw with a line width of 1.
    return SDL_RenderFillRect(rend, &rect);
  }

  // Simply expand the rectangle by the lineWidth.
  const float halfWidth = lineWidth / 2.0f;
  const SDL_FRect expandedRect{
    rect.x - halfWidth,
    rect.y - halfWidth,
    rect.w + lineWidth,
    rect.h + lineWidth
  };

  return SDL_RenderFillRect(rend, &expandedRect);
}

bool aDrawEllipse(SDL_Renderer *rend, float x, float y, float rx, float ry) {
  ShorthandResult shorthandRes = aEllipseShorthand(rend, x, y, rx, ry);
  if (shorthandRes.shorthanded) {
    return shorthandRes.success;
  }

  std::vector<SDL_FPoint> points{aEllipsePoints(x, y, rx, ry)};
  return SDL_RenderPoints(rend, points.data(), points.size());
}

bool aDrawEllipseFill(
  SDL_Renderer *rend, float x, float y, float rx, float ry
) {
  ShorthandResult shorthandRes = aEllipseShorthand(rend, x, y, rx, ry);
  if (shorthandRes.shorthanded) {
    return shorthandRes.success;
  }

  // There is probably a more efficient way to do this
  std::vector<SDL_FPoint> points{aEllipsePoints(x, y, rx, ry)};
  return SDL_RenderLines(rend, points.data(), points.size());
}
} // namespace katze
