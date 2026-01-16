#include <doctest/doctest.h>
#include "core/Align.hpp"

namespace katze {
TEST_CASE("[katze] Test offset function") {
  SUBCASE("Start align offsets") {
    CHECK(offset(50.0f, 25.0f, Align::START) == 0.0f);
    CHECK(offset(50.0f, 50.0f, Align::START) == 0.0f);
    CHECK(offset(50.0f, 60.0f, Align::START) == 0.0f);
  }

  SUBCASE("Center align offsets") {
    CHECK(offset(60.0f, 20.0f, Align::CENTER) == 20.0f);
    CHECK(offset(50.0f, 50.0f, Align::CENTER) == 0.0f);
    CHECK(offset(40.0f, 60.0f, Align::CENTER) == -10.0f);
  }

  SUBCASE("End align offsets") {
    CHECK(offset(60.0f, 20.0f, Align::END) == 40.0f);
    CHECK(offset(50.0f, 50.0f, Align::END) == 0.0f);
    CHECK(offset(40.0f, 60.0f, Align::END) == -20.0f);
  }

  SUBCASE("Offset with negative sizes") {
    SUBCASE("Parent size is negative") {
      CHECK(offset(-10.0f, 20.0f, Align::START) == 0.0f);
      CHECK(offset(-10.0f, 20.0f, Align::CENTER) == -10.0f);
      CHECK(offset(-10.0f, 20.0f, Align::END) == -20.0f);
    }

    SUBCASE("Child size is negative") {
      CHECK(offset(20.0f, -10.0f, Align::START) == 0.0f);
      CHECK(offset(20.0f, -10.0f, Align::CENTER) == 10.0f);
      CHECK(offset(20.0f, -10.0f, Align::END) == 20.0f);
    }

    SUBCASE("Parent and child sizes are negative") {
      CHECK(offset(-20.0f, -10.0f, Align::START) == 0.0f);
      CHECK(offset(-20.0f, -10.0f, Align::CENTER) == 0.0f);
      CHECK(offset(-20.0f, -10.0f, Align::END) == 0.0f);
    }
  }
}
} // namespace katze
