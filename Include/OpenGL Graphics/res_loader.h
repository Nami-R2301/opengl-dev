//
// Created by nami on 5/20/22.
//

#ifndef OPENGL_DEV_RES_LOADER_H
#define OPENGL_DEV_RES_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "vertex.h"

class Resource_loader
{
public:
  explicit Resource_loader(const char *file_path);
  const std::vector<Vertex> &load_vertices();
  const std::vector<GLuint> &load_faces();
  ~Resource_loader();
private:
  std::ifstream file_stream;
};

#endif //OPENGL_DEV_RES_LOADER_H
