#include "./src/tga-image-api/tgaimage.h"
#include <cmath>
#include <ratio>
#include <utility>

// NOTE: TGAColor uses BGRA order instead of RGBA
constexpr TGAColor white = {255, 255, 255, 255};
constexpr TGAColor blue = {255, 0, 0, 255};
constexpr TGAColor green = {0, 255, 0, 255};
constexpr TGAColor red = {0, 0, 255, 255};
constexpr TGAColor yellow = {0, 200, 255, 255};

void drawNonSteepLine(int x0, int y0, int x1, int y1, TGAImage &framebuffer,
                      TGAColor color) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;

  // dy < 0 -> the line is rising
  // NOTE: "y" needs to decrease to rise
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }

  int decision = (dy << 1) - dx;
  int y = y0;

  for (int x{x0}; x <= x1; x++) {
    framebuffer.set(x, y, color);
    if (decision > 0) {
      y += yi;
      decision += (dy - dx) << 1;
    } else {
      decision += dy << 1;
    }
  }
}

void drawSteepLine(int x0, int y0, int x1, int y1, TGAImage &framebuffer,
                   TGAColor color) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;

  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }

  int decision = (dx << 1) - dy;
  int x = x0;

  for (int y{y0}; y <= y1; y++) {
    framebuffer.set(x, y, color);
    if (decision > 0) {
      x += xi;
      decision += (dx - dy) << 1;
    } else {
      decision += dx << 1;
    }
  }
}

void drawLine(int x0, int y0, int x1, int y1, TGAImage &framebuffer,
              TGAColor color) {
  if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
    // NOTE: We draw from left to right
    // Thus, we call the drawNonSteepLine function in a way
    // that we make sure we pass the left point first to the function
    if (x0 > x1)
      drawNonSteepLine(x1, y1, x0, y0, framebuffer, color);
    else
      drawNonSteepLine(x0, y0, x1, y1, framebuffer, color);
  } else {
    if (y0 > y1)
      drawSteepLine(x1, y1, x0, y0, framebuffer, color);
    else
      drawSteepLine(x0, y0, x1, y1, framebuffer, color);
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
