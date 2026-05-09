#include "mesh.h"

Mesh::Mesh(const std::string& obj_path) {
  loadMeshData(obj_path);
}

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

