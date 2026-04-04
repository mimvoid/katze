#ifndef KATZE_ICONS_HPP
#define KATZE_ICONS_HPP

/**
 * katze renders its icons using an array of bits, with a set bit indicating a
 * filled pixel. Much of this was based on raygui's implementation!
 */

#include <array>
#include <cstdint>
#include <vector>

// Length (number of pixels) of a row or column for a katze icon.
#define KATZE_ICON_SIZE 16

// Number of bits required for a katze icon.
#define KATZE_ICON_BIT_SIZE (KATZE_ICON_SIZE * KATZE_ICON_SIZE)

// Number of uint32_t items needed to represent a katze icon.
#define KATZE_ICON_ITEM_COUNT (KATZE_ICON_BIT_SIZE / (sizeof(uint32_t) * 8))

#define KATZE_ICON_MAX_ICONS 256

struct SDL_Renderer;
struct SDL_FRect;

namespace katze {
/**
 * Bit representation of a pixelated monochrome icon.
 *
 * A set bit (1) indicates a filled pixel.
 */
using IconBits = std::array<uint32_t, KATZE_ICON_ITEM_COUNT>;

/**
 * Icon set that stores icon bits in a continuous array.
 */
struct IconSet {
  std::array<uint32_t, KATZE_ICON_ITEM_COUNT * KATZE_ICON_MAX_ICONS> array{};

  /**
   * Get the nth IconBits without bounds checking.
   */
  IconBits operator[](size_t n) const;

  /**
   * Get the nth IconBits with bounds checking.
   * @returns The nth IconBits in the icon set.
   * @throws `std::out_of_range` if `n >= KATZE_ICON_MAX_ICONS`.
   */
  IconBits at(size_t n) const;

  /**
   * Returns the number of icons in the icon set.
   */
  constexpr size_t size() const noexcept { return array.size(); }
};

/**
 * Get the rectangles to render the icon at the given position and size.
 *
 * @param iconBits Bit representation of the icon.
 * @param posX x-coordinate of the icon's top left corner.
 * @param posY y-coordinate of the icon's top left corner.
 * @param pixelSize Size of one pixel in the icon.
 */
std::vector<SDL_FRect> iconAsRects(
  const IconBits &iconBits, float posX, float posY, float pixelSize = 1.0f
);

/**
 * Render an icon.
 *
 * @param rend Renderer to draw on.
 * @param iconBits Bit representation of the icon.
 * @param posX x-coordinate of the icon's top left corner.
 * @param posY y-coordinate of the icon's top left corner.
 * @param pixelSize Size of one pixel in the icon.
 */
void drawIcon(
  SDL_Renderer *rend,
  const IconBits &iconBits,
  float posX,
  float posY,
  float pixelSize = 1.0f
);

/**
 * Render an icon.
 *
 * @param rend Renderer to draw on.
 * @param iconId Icon in the set to draw.
 * @param iconSet Set with the icon.
 * @param posX x-coordinate of the icon's top left corner.
 * @param posY y-coordinate of the icon's top left corner.
 * @param pixelSize Size of one pixel in the icon.
 */
void drawIcon(
  SDL_Renderer *rend,
  uint8_t iconId,
  const IconSet &iconSet,
  float posX,
  float posY,
  float pixelSize = 1.0f
);
} // namespace katze

#endif // !KATZE_ICONS_HPP
