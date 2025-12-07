#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

#pragma pack(push, 1)
struct TGAHeader {
  std::uint8_t idlength = 0;
  std::uint8_t colormaptype = 0;
  std::uint8_t datatypecode = 0;
  std::uint16_t colormaporigin = 0;
  std::uint16_t colormaplength = 0;
  std::uint8_t colormapdepth = 0;
  std::uint8_t x_origin = 0;
  std::uint8_t y_origin = 0;
  std::uint8_t width = 0;
  std::uint16_t heigth = 0;
  std::uint8_t bitsperpixel = 0;
  std::uint8_t imagedesccriptor = 0;
};
#pragma pack(pop)

struct TGAColor {
  std::uint8_t bgra[4] = {
      0,
      0,
      0,
      0,
  };
  std::uint8_t bytespp = 4;
  std::uint8_t &operator[](const int i) { return bgra[i]; }
};

struct TGAImage {
  /*
   * The following enumerator representes
   * the number of "bytes" needed to store per pixel. That is
   * GRAYSCALE = 1 Byte -> 8 bits per pixel
   * RGB = 3 Bytes -> 24 bits per pixel
   * RGBA = 4 Bytes -> 32 bits per pixel
   */
  enum Format { GRAYSCALE = 1, RGB = 3, RGBA = 4 };

  // Default Constructor
  TGAImage() = default;
  TGAImage(const int w, const int h, const int bpp);
  bool read_tga_file(const std::string filename);
  bool write_tga_file(const std::string filename, const bool vflip = true,
                      const bool rle = true) const;
  void flip_horizontally();
  void flip_vertically();
  TGAColor get(const int x, const int y, const TGAColor &c);
  int width() const;
  int heigth() const;

private:
  bool load_rle_data(std::ifstream &in);
  bool unload_rle_data(std::ofstream &out) const;
  int w = 0, h = 0;
  std::uint8_t bpp = 0;
  std::vector<std::uint8_t> data = {};
};
