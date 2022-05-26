//
// Created by nami on 5/20/22.
//

#ifndef OPENGL_DEV_RES_LOADER_H
#define OPENGL_DEV_RES_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../../Include/OpenGL Graphics/mesh.h"
#include "vertex.h"

class Resource_loader
{
public:
  explicit Resource_loader(const char *file_path);
  static std::string load_shader_source(const char *filename);
  Mesh load_mesh();
  ~Resource_loader();
private:
  std::ifstream file_stream;
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
};

#endif //OPENGL_DEV_RES_LOADER_H
