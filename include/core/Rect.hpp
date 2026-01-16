#ifndef KATZE_CORE_RECT_HPP
#define KATZE_CORE_RECT_HPP

#include <type_traits>
#include "Axis.hpp"
#include "Edges.hpp"

namespace katze {
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
struct Rect {
  using value_type = T;

  T x{0};
  T y{0};
  T w{0}; // width
  T h{0}; // height

  constexpr bool operator==(const Rect &that) const {
    return (x == that.x) && (y == that.y) && (w == that.w) && (h == that.h);
  }
  constexpr bool operator!=(const Rect &that) const { return !(*this == that); }

  // Get the position coordinate of the given axis.
  constexpr T position(Axis axis) const { return (axis == Axis::X) ? x : y; }

  // Set the position coordinate of the given axis.
  constexpr void setPosition(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }

  // Get the size (width or height) according to the given axis.
  constexpr T size(Axis axis) const { return (axis == Axis::X) ? w : h; }

  // Set the size (width or height) according to the given axis.
  constexpr void setSize(Axis axis, T value) {
    switch (axis) {
    case Axis::X: w = value; break;
    case Axis::Y: h = value; break;
    }
  }

  /**
   * Set the sizes of both axes.
   *
   * @param axis The given axis.
   * @param axisValue Value to set for the given axis.
   * @param antiAxisValue Value to set for the opposite of the given axis.
   */
  constexpr void setSizes(Axis axis, T axisValue, T antiAxisValue) {
    switch (axis) {
    case Axis::X:
      w = axisValue;
      h = antiAxisValue;
      break;
    case Axis::Y:
      w = antiAxisValue;
      h = axisValue;
      break;
    }
  }

  // Add to the x-axis.
  constexpr void translateX(T dx) { x += dx; }

  // Add to the y-axis.
  constexpr void translateY(T dy) { y += dy; }

  // Add to the position coordinates.
  constexpr void translate(T dx, T dy) {
    x += dx;
    y += dy;
  }

  // Add to a position coordinate by axis.
  constexpr void translate(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x += value; break;
    case Axis::Y: y += value; break;
    }
  }

  // Shrink the width and height.
  constexpr void clip(T dw, T dh) {
    w -= dw;
    h -= dh;
  }

  // Shrink a size by axis.
  constexpr void clip(Axis axis, T value) {
    switch (axis) {
    case Axis::X: w -= value; break;
    case Axis::Y: h -= value; break;
    }
  }

  constexpr void translateClip(T dx, T dy) {
    translate(dx, dy);
    clip(dx, dy);
  }
  constexpr void translateClip(Axis axis, T value) {
    switch (axis) {
    case Axis::X:
      x += value;
      w -= value;
      break;
    case Axis::Y:
      y += value;
      h -= value;
      break;
    }
  }

  constexpr void shrink(Edges<T> padding) {
    x += padding.left;
    y += padding.top;
    w -= padding.getX();
    h -= padding.getY();
  }

  constexpr void expand(Edges<T> margin) {
    x -= margin.left;
    y -= margin.top;
    w += margin.getX();
    h += margin.getY();
  }
};

typedef Rect<int> IRect;
typedef Rect<float> FRect;
} // namespace katze

#endif // !KATZE_CORE_RECT_HPP
