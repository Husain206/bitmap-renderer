#include "bmp.h"
#include <fstream>
#include <ios>
using namespace std;

int main(void) {
  ofstream fout("output.bmp", ios::binary);
  BmpHeader bmpHdr;
  BmpInfoHeader bmpInfoHdr;
  Pixel img[HEIGHT][WIDTH];
  fout.write((char *)&bmpHdr, BMP_HDR_SIZE);
  fout.write((char *)&bmpInfoHdr, BMP_INFO_HDR_SIZE);
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      img[y][x] = BLACK;
    }
  }

  vec3 cube_rot[8];
  for (int i = 0; i < 8; i++)
    cube_rot[i] = cube[i];
  draw_cube(img, cube_rot, edges, edge_colors);

  draw_spider(img);
  for (int y = HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < WIDTH; x++) {
   fout.write((char *)&img[y][x], 3);
    }
  }

  fout.close();

  return 0;
}

// BMP writes pixels bottom → top by default.
// So your image might appear flipped vertically.
// Loop like this instead:
// for(int y = HEIGHT - 1; y >= 0; y--){
