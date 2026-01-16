#ifndef KATZE_CORE_VEC2_HPP
#define KATZE_CORE_VEC2_HPP

#include "Axis.hpp"

namespace katze {
template <typename T>
struct Vec2 {
  using value_type = T;

  T x{0};
  T y{0};

  constexpr Vec2() : Vec2(0, 0) {}
  constexpr Vec2(T val) : Vec2(val, val) {}
  constexpr Vec2(T x, T y) : x(x), y(y) {}

  // Conversion constructors

  template <typename A, typename B>
  constexpr Vec2(A x, B y)
    : x(static_cast<T>(x)), y(static_cast<T>(y)) {}

  template <typename A>
  constexpr Vec2(const Vec2<A> &that)
    : x(static_cast<T>(that.x)), y(static_cast<T>(that.y)) {}

  // Operators

  constexpr bool operator==(const Vec2 &that) const {
    return x == that.x && y == that.y;
  }
  constexpr bool operator!=(const Vec2 &that) const { return !(*this == that); }

  // Methods

  constexpr T get(Axis axis) const { return (axis == Axis::X) ? x : y; }

  constexpr void set(Axis axis, T value) {
    switch (axis) {
    case Axis::X: x = value; break;
    case Axis::Y: y = value; break;
    }
  }
};

typedef Vec2<float> FVec2;
typedef Vec2<int> IVec2;
typedef Vec2<unsigned int> UVec2;
} // namespace katze

#endif // !KATZE_CORE_VEC2_HPP
