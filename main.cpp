#include "./src/tga-image-api/tgaimage.h"
#include <cmath>
#include <utility>

// NOTE: TGAColor uses BGRA order instead of RGBA
constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor blue = {255, 0, 0, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void drawLine(int x0, int y0, int x1, int y1, TGAImage &framebuffer,
              TGAColor color) {
  const int dx = x1 - x0;
  const int dy = y1 - y0;
  bool steep = dy > dx;
  if (steep) {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  int decision = (dy << 1) - dx;
  int y = y0;

  for (int x{x0}; x <= x1; x++) {
    if (steep) {
      framebuffer.set(y, x, color);
    } else {

      framebuffer.set(x, y, color);
    }
    // decision: d0 - d1 -> Thus, if it is positive
    // then the pixel above "p" must be colored.
    if (decision > 0) {
      y++;
      decision += (dy - dx) << 1;
    } else {
      decision += dy << 1;
    }
  }
}

int main() {

  constexpr int width = 64;
  constexpr int height = 64;
  TGAImage framebuffer(width, height, TGAImage::RGB);

  int ax = 7, ay = 3;
  int bx = 12, by = 37;
  int cx = 62, cy = 53;

  drawLine(ax, ay, bx, by, framebuffer, blue);
  drawLine(cx, cy, bx, by, framebuffer, green);
  drawLine(cx, cy, ax, ay, framebuffer, yellow);
  drawLine(ax, ay, cx, cy, framebuffer, red);

  // NOTE: Here I color the vertices so they are clear in
  // the output image.
  framebuffer.set(ax, ay, white);
  framebuffer.set(bx, by, white);
  framebuffer.set(cx, cy, white);

  framebuffer.write_tga_file("framebuffer.tga");

  return 0;
}
