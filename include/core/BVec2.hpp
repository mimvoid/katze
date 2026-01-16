#ifndef KATZE_CORE_BVEC2_HPP
#define KATZE_CORE_BVEC2_HPP

#include <cstdint>
#include "Axis.hpp"

namespace katze {
/**
 * Vector-like bitfield with single bit boolean values.
 */
struct BVec2 {
  bool x : 1;
  bool y : 1;

  // Default constructor, sets both fields to false.
  constexpr BVec2() : BVec2(false) {}

  // Constructor that initializes both fields to a value.
  constexpr BVec2(bool value) : BVec2(value, value) {}

  constexpr BVec2(bool x, bool y) : x(x), y(y) {}

  constexpr bool operator==(const BVec2 &that) const {
    return (x == that.x) && (y == that.y);
  }
  constexpr bool operator!=(const BVec2 &that) const {
    return !(*this == that);
  }

  constexpr operator uint8_t() const { return (x << 1) | y; }

  // Get the value for an axis.
  constexpr bool get(Axis axis) const {
    switch (axis) {
    case Axis::X: return x;
    case Axis::Y: return y;
    }
  }

  // Set the value for an axis.
  constexpr void set(Axis axis, bool value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }
};
}; // namespace katze

#endif // !KATZE_CORE_BVEC2_HPP
