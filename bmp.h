#include <cmath>
#include <cstdint>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using i32 = int32_t;

#define BMP_HDR_SIZE 14
#define BMP_INFO_HDR_SIZE 40

// A bitmap file basically consists of a header of variable size,
// however most commonly used header is of 54 bytes
// size of meta data (14(for bmphdr) + 40(bmpinfohdr) = 54 bytes)
#define BMP_HEADER_INFO_SIZE (14 + 40)

// As we are creating a 512 by 512 bitmap
// size of pixels (512 * 512 * 3 = 786432, each pixel is of 3 bytes in 24 bit
// bitmap file)
#define BMP_PIXELS_3BIT_SIZE (512 * 512 * 3)

#define WIDTH 512
#define HEIGHT 512

#define GREEN {0, 255, 0}
#define BLUE {255, 0, 0}
#define RED {0, 0, 255}
#define BLACK {0, 0, 0}
#define WHITE {255, 255, 255}

#pragma pack(push, 1) // set alignment to 1
struct BmpHeader {
  // The first two bytes 'B' and 'M' are unique to the bitmap file format (there
  // still are different versions of it check bitmap format specification)
  char bmp_signature[2] = {'B', 'M'};
  // the total size is the sum of size of meta data and size of pixels
  u32 sizeOfBmpFile = BMP_HEADER_INFO_SIZE + BMP_PIXELS_3BIT_SIZE;
  u32 reservedBytes = 0;
  // contains the offset to the pixel data of the image from the start of the
  // file
  u32 pixelDataOffset = BMP_HEADER_INFO_SIZE;
};

// bmp has various types of info hdr, but the most common one is 40bytes
struct BmpInfoHeader {
  u32 sizeOfInfoHdr = BMP_INFO_HDR_SIZE;
  // the height of bmp file can be negative, when height it is, the first pixel
  // in the file is drawn at top left of img however the standard for bmp files
  // is to use positive height and the first pixel is drawn at bottom left of
  // img followed by other pixels
  i32 height = HEIGHT;
  i32 width = WIDTH;
  u16 numberOfColorPanels = 1; // must be one
  u16 colorDepth = 24;
  u32 compressionMethod = 0;
  u32 rawBmpDataSize = 0;          // generally ignored
  i32 horizontalResolution = 3780; // in pixel per meter
  i32 verticalResolution = 3780;
  // it is not mandatory in a 24bit bmp file to have a color table
  u32 colorTableEntries = 0;
  u32 importantColors = 0;
};

struct Pixel {
  // in BGR order
  u8 blue = 255;
  u8 green = 255;
  u8 red = 0;
};
#pragma pack(pop) // restore previous alignment rules

void regular_write(Pixel img[HEIGHT][WIDTH]);
void draw_square(Pixel img[HEIGHT][WIDTH], int x0, int y0, int x1, int y1, Pixel color);
void draw_circle(Pixel img[HEIGHT][WIDTH], int radius, int x0, int y0, Pixel color);
void draw_line(Pixel img[HEIGHT][WIDTH], int x0, int y0, int x1, int y1,
               Pixel color);
void draw_spider(Pixel img[HEIGHT][WIDTH]);


