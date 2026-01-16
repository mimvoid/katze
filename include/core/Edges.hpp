#ifndef KATZE_CORE_EDGES_HPP
#define KATZE_CORE_EDGES_HPP

#include <cstdint>
#include "Axis.hpp"

namespace katze {
// Edges of a rectangle.
enum class Edge : uint8_t { TOP, RIGHT, BOTTOM, LEFT };

template <typename T>
struct Edges {
  T top{0};
  T right{0};
  T bottom{0};
  T left{0};

  constexpr Edges(T top, T right, T bottom, T left)
    : top(top), right(right), bottom(bottom), left(left) {}

  constexpr Edges(T y, T x) : Edges(y, x, y, x) {}
  constexpr Edges(T val) : Edges(val, val) {}
  constexpr Edges() {}

  constexpr bool operator==(const Edges &other) const {
    return top == other.top && right == other.right && bottom == other.bottom
           && left == other.left;
  }
  constexpr bool operator!=(const Edges &other) const {
    return !(*this == other);
  }

  // Get the value of an edge.
  constexpr T get(Edge edge) const {
    switch (edge) {
    case Edge::TOP:    return top;
    case Edge::RIGHT:  return right;
    case Edge::BOTTOM: return bottom;
    default:           return left;
    }
  }

  // Set an edge's value.
  constexpr void set(Edge edge, T value) {
    switch (edge) {
    case Edge::TOP:    top = value; break;
    case Edge::RIGHT:  right = value; break;
    case Edge::BOTTOM: bottom = value; break;
    case Edge::LEFT:   left = value; break;
    }
  }

  // Get the sum of the horizontal values.
  constexpr T getX() const { return left + right; }

  // Get the sum of the vertical values.
  constexpr T getY() const { return top + bottom; }

  // Get the sum of the values by axis.
  constexpr T getSum(Axis axis) const {
    return (axis == Axis::X) ? getX() : getY();
  }

  /**
   * Assign all edges to one value.
   * @param value Value to assign
   */
  constexpr void set(T value) {
    top = value;
    right = value;
    bottom = value;
    left = value;
  }

  /**
   * Assign edge values by axis.
   * @param y Value for the top and bottom edges
   * @param x Value for left and right edges
   */
  constexpr void set(T y, T x) {
    top = y;
    right = x;
    bottom = y;
    left = x;
  }
};

typedef Edges<int> IEdges;
typedef Edges<float> FEdges;
} // namespace katze

#endif // !KATZE_CORE_EDGES_HPP
