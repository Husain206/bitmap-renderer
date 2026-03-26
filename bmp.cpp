#include "bmp.h"

void regular_write(Pixel img[HEIGHT][WIDTH]) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      img[y][x].red = (u8)(x * (255 / 4) / WIDTH);    // horizontal gradient
      img[y][x].green = (u8)(y * (255 / 2) / HEIGHT); // vertical
      img[y][x].blue = (u8)(x * (255 / 3) / WIDTH);
    }
  }
}

