#if INTERFACE
typedef struct Color {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Color;
#include "SDL2/SDL.h"
#endif

#include "colors.h"

void Color_Set(SDL_Renderer* renderer, Color toset) {
  SDL_SetRenderDrawColor(renderer, toset.r, toset.g, toset.b, 255);
}

Color ColorFromHSV (unsigned char h, unsigned char s, unsigned char v) {
    Color rgb;
    unsigned char region, remainder, p, q, t;

    if (s == 0)
    {
        rgb.r = v;
        rgb.g = v;
        rgb.b = v;
        return rgb;
    }

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region) {
        case 0:
            rgb.r = v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = v;
            break;
        default:
            rgb.r = v; rgb.g = p; rgb.b = q;
            break;
    }
    return rgb;
}
