#include <doctest/doctest.h>
#include "core/Edges.hpp"

namespace katze {
TEST_CASE("[katze] Test Edges") {
  SUBCASE("Equality") {
    const IEdges e1{1, 2, 3, 4};

    SUBCASE("Edges are equal") {
      const IEdges e2{1, 2, 3, 4};
      REQUIRE(e1 == e2);
      REQUIRE(!(e1 != e2));
    }

    SUBCASE("Edges are not equal") {
      const IEdges e2{2, 4, 1, 4};
      REQUIRE(e1 != e2);
      REQUIRE(!(e1 == e2));
    }

    SUBCASE("Edges are aliases") {
      const IEdges &e2 = e1;
      REQUIRE(e1 == e1);
      REQUIRE(!(e1 != e1));
      REQUIRE(e1 == e2);
      REQUIRE(!(e1 != e2));
    }
  }

  SUBCASE("Construct Edges") {
    REQUIRE(IEdges() == IEdges{0, 0, 0, 0});
    REQUIRE(IEdges(1) == IEdges{1, 1, 1, 1});
    REQUIRE(IEdges(1, 2) == IEdges{1, 2, 1, 2});
    REQUIRE(IEdges(1, 2, 3, 4) == IEdges{1, 2, 3, 4});
  }

  SUBCASE("Get Edges value by enum") {
    const IEdges edges{1, 2, 3, 4};

    CHECK(edges.get(Edge::TOP) == 1);
    CHECK(edges.get(Edge::RIGHT) == 2);
    CHECK(edges.get(Edge::BOTTOM) == 3);
    CHECK(edges.get(Edge::LEFT) == 4);
  }

  SUBCASE("Set Edges value by enum") {
    SUBCASE("Top field value") {
      IEdges edges{1, 2, 3, 4};
      edges.set(Edge::TOP, 0);
      CHECK(edges == IEdges{0, 2, 3, 4});
    }

    SUBCASE("Right field value") {
      IEdges edges{1, 2, 3, 4};
      edges.set(Edge::RIGHT, 0);
      CHECK(edges == IEdges{1, 0, 3, 4});
    }

    SUBCASE("Bottom field value") {
      IEdges edges{1, 2, 3, 4};
      edges.set(Edge::BOTTOM, 0);
      CHECK(edges == IEdges{1, 2, 0, 4});
    }

    SUBCASE("Left field value") {
      IEdges edges{1, 2, 3, 4};
      edges.set(Edge::LEFT, 0);
      CHECK(edges == IEdges{1, 2, 3, 0});
    }
  }

  SUBCASE("Get Edges values by axis") {
    const IEdges edges{1, 2, 3, 4};

    CHECK(edges.getSum(katze::Axis::X) == 6);
    CHECK(edges.getSum(katze::Axis::Y) == 4);
  }

  SUBCASE("Set Edges field values") {
    SUBCASE("One value") {
      IEdges edges{1, 2, 3, 4};
      edges.set(5);
      CHECK(edges == Edges{5, 5, 5, 5});
    }

    SUBCASE("Two values") {
      IEdges edges{1, 2, 3, 4};
      edges.set(5, 6);
      CHECK(edges == Edges{5, 6, 5, 6});
    }
  }
}
} // namespace katze
