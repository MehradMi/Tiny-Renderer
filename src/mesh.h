#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>

#include "Vec3D.h"
#include "Triangle.h"

class Mesh {
public:
  Mesh() = delete;
  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;
  Mesh(Mesh&&) noexcept;
  Mesh& operator=(Mesh&&) noexcept;
  ~Mesh() = default;

  Mesh(const std::string& obj_path);

  std::vector<Vec3D> vertices;
  std::vector<Face>  faces;
  Vec3D rotation;

private:
  void loadMeshData(const std::string& obj_path);
};

#endif
