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
#include "triangle.h"

#define NUM_CUBE_VERTICES 8
#define NUM_CUBE_FACES (6 * 2) // 6 cube face & 2 triangles per face 

extern Vec3D cube_vertices[NUM_CUBE_VERTICES];
extern Face cube_faces[NUM_CUBE_FACES];

class Mesh {
  public:
    
    Mesh() = default;
    Mesh(const char* obj_path);

    std::vector<Vec3D> vertices;
    std::vector<Face>  faces;
    Vec3D rotation;

    void loadMeshData(const std::string& obj_path);

  private:
};

extern Mesh myMesh;

void load_cube_mesh_data(void);

#endif
