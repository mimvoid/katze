#include "icons.hpp"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <doctest/doctest.h>

namespace katze {
IconBits IconSet::operator[](size_t n) const {
  IconBits bits{};
  const size_t startIdx = n * KATZE_ICON_ITEM_COUNT;
  for (size_t i = 0; i < KATZE_ICON_ITEM_COUNT; i++) {
    bits[i] = array[startIdx + i];
  }
  return bits;
}

IconBits IconSet::at(size_t n) const {
  if (n < 0 || n >= KATZE_ICON_MAX_ICONS) {
    return IconBits{}; // Out of bounds.
  }
  return this->operator[](n);
}

std::vector<SDL_FRect>
iconAsRects(const IconBits &bits, float posX, float posY, float pixelSize) {
  std::vector<SDL_FRect> rects{};

  SDL_FRect rect{posX, posY, pixelSize, pixelSize};
  uint8_t col = 0;
  bool lastBit = 0;

  constexpr size_t U32_BITS = sizeof(uint32_t) * 8;

  for (uint32_t bitItem : bits) {
    for (size_t i = 0; i < U32_BITS; i++) {
      if (col == KATZE_ICON_SIZE - 1) {
        // At the end of the row.
        if (lastBit) {
          rect.w += pixelSize;
          rects.push_back(rect);
        } else if (bitItem & (1u << i)) {
          rect.x = posX + (col * pixelSize);
          rect.w = pixelSize;
          rects.push_back(rect);
        }

        col = 0;             // Reset column
        rect.y += pixelSize; // Progress y
        lastBit = 0;
        continue;
      }

      if (bitItem & (1u << i)) {
        if (lastBit) {
          rect.w += pixelSize;
        } else {
          rect.x = posX + (col * pixelSize);
          rect.w = pixelSize;
        }
        lastBit = 1;
      } else {
        if (lastBit) {
          rects.push_back(rect);
        }
        lastBit = 0;
      }

      col++; // Progress column
    }
  }

  return rects;
}

void drawIcon(
  SDL_Renderer *rend,
  const IconBits &bits,
  float posX,
  float posY,
  float pixelSize
) {
  std::vector<SDL_FRect> rects = iconAsRects(bits, posX, posY, pixelSize);
  SDL_RenderFillRects(rend, rects.data(), rects.size());
}

void drawIcon(
  SDL_Renderer *rend,
  uint8_t iconId,
  const IconSet &iconSet,
  float posX,
  float posY,
  float pixelSize
) {
  drawIcon(rend, iconSet.at(iconId), posX, posY, pixelSize);
}

/*********/
/* Tests */
/*********/

TEST_CASE("[katze] IconSet operator [] default constructed") {
  IconSet set{};
  IconBits bits = set[0];
  for (size_t i = 0; i < bits.size(); i++) {
    CHECK(bits[i] == 0);
  }
}

TEST_CASE("[katze] IconSet get first icon") {
  IconSet set{};
  for (size_t i = 0; i < KATZE_ICON_ITEM_COUNT; i++) {
    set.array[i] = i;
  }

  IconBits bits = set[0];
  for (size_t i = 0; i < bits.size(); i++) {
    CHECK(bits[i] == set.array[i]);
  }
}

TEST_CASE("[katze] IconSet get second icon") {
  const size_t offset = KATZE_ICON_ITEM_COUNT;
  IconSet set{};
  for (size_t i = 0; i < KATZE_ICON_ITEM_COUNT; i++) {
    set.array[offset + i] = i;
  }

  IconBits bits = set[1];
  for (size_t i = 0; i < bits.size(); i++) {
    CHECK(bits[i] == set.array[offset + i]);
  }
}

TEST_CASE("[katze] IconSet get last icon") {
  IconSet set{};
  const size_t offset = set.size() - KATZE_ICON_ITEM_COUNT;
  for (size_t i = 0; i < KATZE_ICON_ITEM_COUNT; i++) {
    set.array[offset + i] = i;
  }

  IconBits bits = set[KATZE_ICON_MAX_ICONS - 1];
  for (size_t i = 0; i < bits.size(); i++) {
    CHECK(bits[i] == set.array[offset + i]);
  }
}

TEST_CASE("[katze] IconSet::at() input exceeds size") {
  IconSet set{};
  IconBits bits = set.at(KATZE_ICON_MAX_ICONS);
  for (size_t i = 0; i < bits.size(); i++) {
    CHECK(bits[i] == 0);
  }
}

TEST_CASE("[katze] iconAsRects with unset icon bits") {
  CHECK(iconAsRects(IconBits{}, 0.0f, 0.0f).size() == 0);
}

TEST_CASE("[katze] iconAsRects") {
  float pixelSize = 1.0f;

  SUBCASE("First bit is set") {
    IconBits bits{};
    bits[0] = 1;

    std::vector<SDL_FRect> rects = iconAsRects(bits, 0.0f, 0.0f, pixelSize);
    CHECK(rects.size() == 1);
    CHECK(rects[0].x == 0.0f);
    CHECK(rects[0].y == 0.0f);
    CHECK(rects[0].w == pixelSize);
    CHECK(rects[0].h == pixelSize);
  }

  SUBCASE("Bit at the end of the first row is set") {
    IconBits bits{};
    bits[0] = 1 << (KATZE_ICON_SIZE - 1);

    std::vector<SDL_FRect> rects = iconAsRects(bits, 0.0f, 0.0f, pixelSize);
    CHECK(rects.size() == 1);
    CHECK(rects[0].x == (KATZE_ICON_SIZE - 1) * pixelSize);
    CHECK(rects[0].y == 0.0f);
    CHECK(rects[0].w == pixelSize);
    CHECK(rects[0].h == pixelSize);
  }

  SUBCASE("First row is completely set") {
    IconBits bits{};
    bits[0] = (1 << KATZE_ICON_SIZE) - 1;

    std::vector<SDL_FRect> rects = iconAsRects(bits, 0.0f, 0.0f, pixelSize);
    CHECK(rects.size() == 1);
    CHECK(rects[0].x == 0.0f);
    CHECK(rects[0].y == 0.0f);
    CHECK(rects[0].w == KATZE_ICON_SIZE * pixelSize);
    CHECK(rects[0].h == pixelSize);
  }

  SUBCASE("All bits set") {
    IconBits bits{};
    for (size_t i = 0; i < bits.size(); i++) {
      bits[i] = 0xffffffff;
    }

    std::vector<SDL_FRect> rects = iconAsRects(bits, 0.0f, 0.0f, pixelSize);
    CHECK(rects.size() == KATZE_ICON_SIZE);
    for (size_t i = 0; i < rects.size(); i++) {
      CHECK(rects[i].x == 0.0f);
      CHECK(rects[i].w == KATZE_ICON_SIZE * pixelSize);
      CHECK(rects[i].h == pixelSize);
    }
  }
}
} // namespace katze
