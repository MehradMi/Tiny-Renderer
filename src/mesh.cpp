#include "mesh.h"

void Mesh::loadMeshData(const std::string& obj_path) {
  std::ifstream obj_file;
  obj_file.exceptions(std::ifstream::badbit);
  try {
    obj_file.open(obj_path, std::ios_base::in);
    std::cout << "SUCCESS::MESH::READING_OBJ_FILE_SUCCESSFUL" << std::endl;
  } catch (const std::ifstream::failure& e) {
    std::cerr << "ERROR::MESH::READING_OBJ_FILE_FAILED: " << e.what() << std::endl;
    return;
  }

  if (obj_file.is_open())  {
    // Read file line by line
    std::string line;
    while(std::getline(obj_file, line)) {
      if (line.compare(0, 2, "v ") == 0) {
        Vec3D _vertex;
        std::sscanf(
          line.c_str(), "v %f %f %f",
          &_vertex.x, &_vertex.y, &_vertex.z
        );
        vertices.push_back(_vertex);
      } else if (line.compare(0, 2, "f ") == 0) {
        int vertex_indices[3];
        int texture_indices[3];
        int normal_indices[3];
        std::sscanf(
        line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
          &vertex_indices[0], &texture_indices[0], &normal_indices[0],
          &vertex_indices[1], &texture_indices[1], &normal_indices[1],
          &vertex_indices[2], &texture_indices[2], &normal_indices[2]
        );

        Face _face{
          vertex_indices[0],
          vertex_indices[1],
          vertex_indices[2],
        };

        faces.push_back(_face);
      }
    }
  }
}

Mesh::Mesh(const char* obj_path) {

}

Mesh myMesh{};

Vec3D cube_vertices[NUM_CUBE_VERTICES] = {
  {-1, -1, -1},
  {-1, +1, -1},
  {+1, +1, -1},
  {+1, -1, -1},
  {+1, +1, +1},
  {+1, -1, +1},
  {-1, +1, +1},
  {-1, -1, +1},
};


Face cube_faces[NUM_CUBE_FACES] = {
  // front
  {1, 2, 3},
  {1, 3, 4},
  // right
  {4, 3, 5},
  {4, 5, 6},
  // back
  {6, 5, 7},
  {6, 7, 8},
  // left
  {8, 7, 2},
  {8, 2, 1},
  // top
  {2, 7, 5},
  {2, 5, 3},
  // bottom
  {6, 8, 1},
  {6, 1, 4},
};

void load_cube_mesh_data(void) {
  for (int i{0}; i < NUM_CUBE_VERTICES; i++) {
    Vec3D _cube_vertex = cube_vertices[i];
    myMesh.vertices.push_back(_cube_vertex);
  }

  for (int i{0}; i < NUM_CUBE_FACES; i++) {
    Face _cube_face = cube_faces[i];
    myMesh.faces.push_back(_cube_face);
  }
}
