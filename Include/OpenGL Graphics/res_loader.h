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
  ~Resource_loader();

  static std::string load_shader_source(const char *file_path);
  static Texture load_texture_file(const char *file_path);
  void load_mesh();

  const std::vector<Vertex> &get_vertices() const;
  const std::vector<GLuint> &get_indices() const;
private:
  std::ifstream file_stream;
  std::vector<Vertex> vertices;
  std::vector<GLuint> indices;
  std::vector<Vector_2f> texCoords;

  void load_vertices(std::stringstream &ss);
  void load_indices(std::stringstream &ss, std::string &line);
  void load_textures(std::stringstream &ss);
  void set_vertex_textures();
};

#endif //OPENGL_DEV_RES_LOADER_H
