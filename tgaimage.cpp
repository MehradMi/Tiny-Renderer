#include "tgaimage.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>

TGAImage::TGAImage(const int w, const int h, const int bpp)
    : w(w), h(h), bpp(bpp), data(w * h * bpp, 0) {};

// TGAImage struct member function -> used for reading from a ".tga" file
bool TGAImage::read_tga_file(const std::string filename) {
  std::fstream in;
  in.open(filename, std::ios::binary);
  if (!in.is_open()) {
    std::cerr << "Can't open file " << filename << std::endl;
    return false;
  }
  TGAHeader header;
  in.read(reinterpret_cast<char *>(&header), sizeof(header));
  if (!in.good()) {
    std::cerr << "An error has occured during reading the header" << std::endl;
    return false;
  }
  w = header.width;
  h = header.heigth;
  bpp = header.bitsperpixel >>
        3; // Shifting bits right by 3 -> because its faster than dividing by 8!
  if (w <= 0 || h <= 0 || (bpp != GRAYSCALE && bpp != RGB && bpp != RGBA)) {
    std::cerr << "Bad bpp (or width/heigth) value" << std::endl;
    return false;
  }
  size_t nbytes = bpp * w * h;
  data = std::vector<std::uint8_t>(nbytes, 0);
}
