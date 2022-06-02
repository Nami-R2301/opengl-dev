//
// Created by nami on 5/20/22.
//

#ifndef OPENGL_DEV_RES_LOADER_H
#define OPENGL_DEV_RES_LOADER_H

#include <fstream>
#include <string>
#include <vector>

#include "vertex.h"
#include "texture.h"

typedef struct res_loader_s
{
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Vector_2f> texCoords;
} res_loader_t;

res_loader_t load_mesh(const char *file_path);
std::string load_shader_source(const char *file_path);
Texture load_texture_file(const char *file_path);

void load_vertices(std::stringstream &ss, res_loader_t &mesh_s);
void load_indices(std::stringstream &ss, std::string &line, res_loader_t &mesh_s);
void load_textures(std::stringstream &ss, res_loader_t &mesh_s);
void set_vertex_textures(res_loader_t &mesh_s);

#endif //OPENGL_DEV_RES_LOADER_H
