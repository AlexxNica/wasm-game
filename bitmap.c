
#include <string.h>
#include "bitmap.h"

#define DIM 16

uint32_t *bitmap_offset(bitmap_t *s, int x, int y) {
  return s->at + ((s->w * y) + x);
}

int memcpy_word(uint32_t *restrict dst, const uint32_t *restrict src, int n) {
  while (n > 0) {
    dst[0] = src[0];
    ++dst;
    ++src;
    --n;
  }
  return 0;
}

int spriteset_blit(bitmap_t *from, int i, bitmap_t *to, int x, int y) {
  int fx = (i * DIM) % from->w;
  int fy = ((i * DIM) / from->w) * DIM;

  uint32_t *src = bitmap_offset(from, fx, fy);
  uint32_t *dst = bitmap_offset(to, x, y);

  for (int j = 0; j < DIM; ++j) {
    memcpy_word(dst, src, DIM);
    src += from->w;
    dst += to->w;
  }

  return 0;
}

int spriteset_blit_trans(bitmap_t *from, int i, bitmap_t *to, int x, int y) {
  int fx = (i * DIM) % from->w;
  int fy = ((i * DIM) / from->w) * DIM;

  uint32_t *src = bitmap_offset(from, fx, fy);
  uint32_t *dst = bitmap_offset(to, x, y);

  for (int j = 0; j < DIM; ++j) {
    for (int q = 0; q < DIM; ++q) {
      if (src[q] & 0x000000ff) {
        dst[q] = src[q];
      }
    }
    src += from->w;
    dst += to->w;
  }

  return 0;
}

int bitmap_set(bitmap_t *b, int x, int y, uint32_t v) {
  if (x < 0 || y < 0 || x >= b->w || y >= b->h) {
    return -1;
  }

  uint32_t *target = bitmap_offset(b, x, y);
  uint32_t prev = *target;
  *target = v;
  return prev;
}
