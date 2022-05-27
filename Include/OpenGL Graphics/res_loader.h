//
// Created by nami on 5/20/22.
//

#ifndef OPENGL_DEV_RES_LOADER_H
#define OPENGL_DEV_RES_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "mesh.h"
#include "vertex.h"
#include "texture.h"

class Resource_loader
{
public:
  explicit Resource_loader(const char *file_path);
  static std::string load_shader_source(const char *file_path);
  std::vector<Vertex> load_vertices() const;
  std::vector<GLuint> load_indices() const;
  static Texture load_texture(const char *file_path);
  void load_mesh();
  ~Resource_loader();
private:
  std::ifstream file_stream;
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<GLuint> textures;
};

#endif //OPENGL_DEV_RES_LOADER_H
