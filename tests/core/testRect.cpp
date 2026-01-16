#include <doctest/doctest.h>
#include "core/Rect.hpp"

namespace katze {
TEST_CASE("[katze] Test FRect") {
  SUBCASE("Equality operators") {
    SUBCASE("FRects are equal") {
      const FRect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const FRect r2{1.0f, 2.0f, 40.0f, 90.0f};

      REQUIRE(r1 == r2);
      REQUIRE(!(r1 != r2));
    }

    SUBCASE("FRects are not equal") {
      const FRect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const FRect r2{2.0f, 2.0f, 40.0f, 80.0f};

      REQUIRE(r1 != r2);
      REQUIRE(!(r1 == r2));
    }

    SUBCASE("FRects are aliases") {
      const FRect r1{1.0f, 2.0f, 40.0f, 90.0f};
      const FRect &r2 = r1;

      REQUIRE(r1 == r1);
      REQUIRE(!(r1 != r1));

      REQUIRE(r1 == r2);
      REQUIRE(!(r1 != r2));
    }
  }

  SUBCASE("Get FRect position by axis") {
    const FRect rect{1.0f, 2.0f, 40.0f, 90.0f};

    CHECK(rect.position(katze::Axis::X) == 1.0f);
    CHECK(rect.position(katze::Axis::Y) == 2.0f);
  }

  SUBCASE("Set FRect position by axis") {
    SUBCASE("Set position by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setPosition(katze::Axis::X, 10.0f);
      CHECK(rect == FRect{10.0f, 2.0f, 40.0f, 90.0f});
    }

    SUBCASE("Set position by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setPosition(katze::Axis::Y, 10.0f);
      CHECK(rect == FRect{1.0f, 10.0f, 40.0f, 90.0f});
    }
  }

  SUBCASE("Get FRect size by axis") {
    const FRect rect{1.0f, 2.0f, 40.0f, 90.0f};

    CHECK(rect.size(katze::Axis::X) == 40.0f);
    CHECK(rect.size(katze::Axis::Y) == 90.0f);
  }

  SUBCASE("Set FRect size by axis") {
    SUBCASE("Set size by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setSize(katze::Axis::X, 10.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 10.0f, 90.0f});
    }

    SUBCASE("Set size by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.setSize(katze::Axis::Y, 10.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 40.0f, 10.0f});
    }
  }

  SUBCASE("Translate x and y") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translate(5.0f, 5.0f);
    CHECK(rect == FRect{6.0f, 7.0f, 40.0f, 90.0f});
  }

  SUBCASE("Translate by axis") {
    SUBCASE("Translate by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translate(katze::Axis::X, 5.0f);
      CHECK(rect == FRect{6.0f, 2.0f, 40.0f, 90.0f});
    }

    SUBCASE("Translate by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translate(katze::Axis::Y, -5.0f);
      CHECK(rect == FRect{1.0f, -3.0f, 40.0f, 90.0f});
    }
  }

  SUBCASE("Clip width and height") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.clip(10.0f, -20.0f);
    CHECK(rect == FRect{1.0f, 2.0f, 30.0f, 110.0f});
  }

  SUBCASE("Clip by axis") {
    SUBCASE("Clip by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.clip(katze::Axis::X, 5.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 35.0f, 90.0f});
    }

    SUBCASE("Clip by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.clip(katze::Axis::Y, -5.0f);
      CHECK(rect == FRect{1.0f, 2.0f, 40.0f, 95.0f});
    }
  }

  SUBCASE("Translate clip") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    rect.translateClip(10.0f, -20.0f);
    CHECK(rect == FRect{11.0f, -18.0f, 30.0f, 110.0f});
  }

  SUBCASE("Translate clip by axis") {
    SUBCASE("Translate clip by x-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translateClip(katze::Axis::X, 5.0f);
      CHECK(rect == FRect{6.0f, 2.0f, 35.0f, 90.0f});
    }

    SUBCASE("Translate clip by y-axis") {
      FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
      rect.translateClip(katze::Axis::Y, -5.0f);
      CHECK(rect == FRect{1.0f, -3.0f, 40.0f, 95.0f});
    }
  }

  SUBCASE("Pad FRect") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    const katze::FEdges padding{1, 2, 5, 1};
    rect.shrink(padding);
    CHECK(rect == FRect{2.0f, 3.0f, 37.0f, 84.0f});
  }

  SUBCASE("Expand FRect") {
    FRect rect{1.0f, 2.0f, 40.0f, 90.0f};
    const katze::FEdges margin{1, 2, 5, 1};
    rect.expand(margin);
    CHECK(rect == FRect{0.0f, 1.0f, 43.0f, 96.0f});
  }
}
} // namespace katze
