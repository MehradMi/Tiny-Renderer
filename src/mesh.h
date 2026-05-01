#ifndef MESH_H
#define MESH_H

#include "vector.h"
#include "triangle.h"
#include <vector>

#define NUM_CUBE_VERTICES 8
#define NUM_CUBE_FACES (6 * 2) // 6 cube face & 2 triangles per face 

extern Vec3D cube_vertices[NUM_CUBE_VERTICES];
extern Face cube_faces[NUM_CUBE_FACES];

struct Mesh {
  std::vector<Vec3D> vertices;
  std::vector<Face>  faces;
  Vec3D rotation;
};

extern Mesh myMesh;

void load_cube_mesh_data(void);

#endif
