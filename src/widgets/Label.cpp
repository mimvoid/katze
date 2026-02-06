#include "widgets/Label.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "ctx/Dctx.hpp"

namespace katze {
Label::~Label() { TTF_DestroyText(textPtr); }

void Label::resize(Gctx g, FRect &rect) { resizeForFont(g.font, g, rect); }
void Label::view(Dctx &d, FRect rect) { viewForFont(d.root.font(), d, rect); }

void Label::resizeForFont(Font font, const Gctx &g, FRect &rect) {
  if (empty()) {
    rect.w = 0;
    rect.h = 0;
    return;
  }

  int width = 0;
  int height = 0;
  const int wrapWidth = wrapWords ? g.w * g.scale : 0;

  if (!textPtr) {
    // Create a new text
    textPtr = TTF_CreateText(g.textEngine, font.data, text, 0);
  }
  if (textPtr) {
    TTF_SetTextFont(textPtr, font.data);
    TTF_SetTextString(textPtr, text, 0);

    // If wrapWords is false, set wrap_width to 0 to still wrap on \n
    TTF_SetTextWrapWidth(textPtr, wrapWidth);
    TTF_GetTextSize(textPtr, &width, &height);
  } else {
    TTF_GetStringSizeWrapped(font.data, text, 0, wrapWidth, &width, &height);
  }

  if (g.scale != 0.0f) {
    // Adjust for display scale
    width /= g.scale;
    height /= g.scale;
  }

  rect.w = g.clampWidth(width);
  rect.h = g.clampHeight(height);
}

void Label::viewForFont(Font font, Dctx &d, FRect rect) {
  if (empty()) {
    return; // Nothing to draw
  }

  if (!textPtr) {
    viewNoTextPtr(font, d, rect);
    return;
  }

  Rgb color = d.colors().text;
  TTF_SetTextColor(textPtr, color.r, color.g, color.b, 255);
  TTF_DrawRendererText(textPtr, rect.x * d.scale, rect.y * d.scale);
}

void Label::viewNoTextPtr(Font font, Dctx &d, FRect rect) {
  Rgb color = d.colors().text;
  SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(
    font.data,
    text,
    0,
    SDL_Color{color.r, color.g, color.b, 255},
    wrapWords ? rect.w * d.scale : 0
  );

  if (surface) {
    SDL_Texture *texture =
      SDL_CreateTextureFromSurface(d.root.sdlRenderer(), surface);

    if (texture) {
      SDL_FRect dst = d.scaledRect(rect);
      SDL_RenderTexture(d.root.sdlRenderer(), texture, nullptr, &dst);
    }

    SDL_DestroyTexture(texture);
  }

  SDL_DestroySurface(surface);
}
} // namespace katze
