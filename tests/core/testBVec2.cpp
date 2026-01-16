#include <doctest/doctest.h>
#include "core/BVec2.hpp"

namespace katze {
TEST_CASE("[katze] BVec2 to uint8_t") {
  CHECK((uint8_t)BVec2{false, false} == 0);
  CHECK((uint8_t)BVec2{false, true} == 1);
  CHECK((uint8_t)BVec2{true, false} == 2);
  CHECK((uint8_t)BVec2{true, true} == 3);
}

TEST_CASE("[katze] Get BVec2 value by axis") {
  const BVec2 v{true, false};

  CHECK(v.get(Axis::X) == true);
  CHECK(v.get(Axis::Y) == false);
}

TEST_CASE("[katze] Set Vec2 value by axis") {
  SUBCASE("Set value by x-axis") {
    BVec2 v{false, false};
    v.set(Axis::X, true);

    CHECK(v.x == true);
    CHECK(v.y == false);
  }

  SUBCASE("Set value by y-axis") {
    BVec2 v{false, true};
    v.set(Axis::Y, false);

    CHECK(v.x == false);
    CHECK(v.y == false);
  }
}
} // namespace katze
