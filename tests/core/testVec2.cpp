#include <doctest/doctest.h>
#include "core/Vec2.hpp"

namespace katze {
TEST_CASE("[katze] Get FVec2 value by axis") {
  const FVec2 v{1.0f, 2.0f};

  CHECK(v.get(Axis::X) == 1.0f);
  CHECK(v.get(Axis::Y) == 2.0f);
}

TEST_CASE("[katze] Set FVec2 value by axis") {
  SUBCASE("Set value by x-axis") {
    FVec2 v{1.0f, 2.0f};
    v.set(Axis::X, 3.0f);

    CHECK(v.x == 3.0f);
    CHECK(v.y == 2.0f);
  }

  SUBCASE("Set value by y-axis") {
    FVec2 v{1.0f, 2.0f};
    v.set(Axis::Y, 3.0f);

    CHECK(v.x == 1.0f);
    CHECK(v.y == 3.0f);
  }
}
} // namespace katze
