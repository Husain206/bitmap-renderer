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

void draw_square(Pixel img[HEIGHT][WIDTH], int x0, int y0, int x1, int y1, Pixel color) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (x > x0 && x < x1 && y > y0 && y < y1) {
        img[y][x] = color;
      }
    }
  }
}

void draw_circle(Pixel img[HEIGHT][WIDTH], int radius, int x0, int y0, Pixel color) {
  // int cx = WIDTH/2;
  // int cy = HEIGHT/2;
  int cx = x0;
  int cy = y0;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int dx = x - cx;
      int dy = y - cy;

      if (dx * dx + dy * dy < radius * radius) {
        img[y][x] = color;
      }
    }
  }
}

void draw_line(Pixel img[HEIGHT][WIDTH], int x0, int y0, int x1, int y1,
               Pixel color) {
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);

  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;

  int err = dx - dy;

  while (true) {
    if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
      img[y0][x0] = color; // white line
    }

    if (x0 == x1 && y0 == y1)
      break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void draw_spider(Pixel img[HEIGHT][WIDTH]){
  draw_line(img, WIDTH / 2, HEIGHT / 2.5, WIDTH - 150, HEIGHT/2, BLUE);    /* \ */ // down
  draw_line(img, WIDTH / 2, HEIGHT / 2.5, 150, HEIGHT/3, RED);                      /* \ */ // up
  draw_line(img, WIDTH / 2, HEIGHT / 2.5, 150, HEIGHT/2, WHITE);               /* / */ // down
  draw_line(img, WIDTH / 2, HEIGHT / 2.5, WIDTH - 150, 170, GREEN);                /* / */ // up
  draw_line(img, 180, HEIGHT / 4.5, WIDTH / 2, HEIGHT / 2.5, WHITE);           /* - */ // left a little up
  draw_line(img, 180, HEIGHT / 1.7, WIDTH / 2, HEIGHT / 2.5, WHITE);         /* - */ // left a little down
  draw_line(img, WIDTH / 2, HEIGHT / 2.5, WIDTH - 180, HEIGHT / 4.5, GREEN);       /* - */ // right a little up
  draw_line(img, WIDTH / 2, HEIGHT / 2.5, WIDTH - 180, HEIGHT / 1.7, GREEN);     /* - */ // right a little down
  draw_line(img, 180, 113, 180, 0, WHITE);
  draw_line(img, WIDTH-180, 113, WIDTH-180, 0, GREEN);
  draw_line(img, 150, 170, 120, 0, GREEN);
  draw_line(img, WIDTH-150, 170, WIDTH-120, 0, GREEN);
  draw_line(img, WIDTH-150, 255, WIDTH-80, HEIGHT, GREEN);
  draw_line(img, 150, 255, 80, HEIGHT, GREEN);
  draw_line(img, 180, 302, 180, HEIGHT, GREEN);
  draw_line(img, WIDTH-180, 302, WIDTH-180, HEIGHT, GREEN);
  draw_circle(img, 30, WIDTH/2, HEIGHT/4, RED);
  draw_circle(img, 50, WIDTH/2, HEIGHT/2.5, RED);
  draw_circle(img, 65, WIDTH/2, HEIGHT/1.7, RED);
}


void project_cube(vec3 cube[8], int projected[8][2]) {
  float scale = WIDTH / 4.f;
  float distance = 2.5f; // distance from camera
  for (int i = 0; i < 8; i++) {
    float factor = distance / (distance - cube[i].z); // perspective
    projected[i][0] = (int)(cube[i].x * scale * factor + WIDTH / 2.f);
    projected[i][1] = (int)(cube[i].y * scale * factor + HEIGHT / 2.f);
  }
}

void rotate_x(vec3 &v, float angle) {
  float rad = angle * 3.14159265f / 180.0f;
  float y = v.y;
  float z = v.z;
  v.y = y * cos(rad) - z * sin(rad);
  v.z = y * sin(rad) + z * cos(rad);
}

void rotate_y(vec3 &v, float angle) {
  float rad = angle * 3.14159265f / 180.0f;
  float x = v.x;
  float z = v.z;
  v.x = x * cos(rad) + z * sin(rad);
  v.z = -x * sin(rad) + z * cos(rad);
}

void rotate_z(vec3 &v, float angle) {
  float rad = angle * 3.14159265f / 180.0f;
  float x = v.x;
  float y = v.y;
  v.x = x * cos(rad) - y * sin(rad);
  v.y = x * sin(rad) + y * cos(rad);
}

void rotate_cube(vec3 cube[8], float angleX, float angleY, float angleZ) {
  for (int i = 0; i < 8; i++) {
    rotate_x(cube[i], angleX);
    rotate_y(cube[i], angleY);
    rotate_z(cube[i], angleZ);
  }
}

void draw_cube(Pixel img[HEIGHT][WIDTH], vec3 cube[8], int edges[12][2],
               Pixel colors[12]) {
  int projected[8][2];
  project_cube(cube, projected);

  for (int i = 0; i < 12; i++) {
    int a = edges[i][0];
    int b = edges[i][1];
    draw_line(img, projected[a][0], projected[a][1], projected[b][0],
              projected[b][1], colors[i]);
  }
}
