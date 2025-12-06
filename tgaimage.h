#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

#pragma pack(push, 1)
struct TGAHeader {
  std::uint8_t idlength = 0;
};
#pragma pack(pop)
