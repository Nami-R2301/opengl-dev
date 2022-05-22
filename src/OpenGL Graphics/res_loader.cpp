//
// Created by nami on 5/20/22.
//
#include "../../Include/OpenGL Graphics/res_loader.h"

Resource_loader::Resource_loader(const char *file_path)
{
  this->file_stream = std::ifstream(file_path);
}

const std::vector<Vertex> &Resource_loader::load_vertices()
{
  return std::vector<Vertex>();
}

const std::vector<GLuint> &Resource_loader::load_faces()
{
  return std::vector<GLuint>();
}

Resource_loader::~Resource_loader()
{
  this->file_stream.close();
}



