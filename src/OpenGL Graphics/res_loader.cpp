//
// Created by nami on 5/20/22.
//
#include "res_loader.h"
#include "../Logs/logger.h"
#include <fstream>

std::string load_shader_source(const char *file_path)
{
  // Add filename to path.
  char relative_file_path[255];
  if (snprintf(relative_file_path, 255, "../Resources/Shaders/%s", file_path) < 0)
  {
    alert(ERROR, "ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...");
    exit(ERROR_SNPRINTF);
  }

  std::ifstream in((relative_file_path), std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], (long) contents.size());
    in.close();
    return contents;
  }
  throw errno;
}

Texture load_texture_file(const char *file_path)
{
  alert(INFO, "LOADING TEXTURE...");
  Texture tex(file_path);
  return tex;
}

res_loader_t load_mesh(const char *file_path)
{
  res_loader_t mesh_s;

  // Add filename to path.
  char relative_file_path[strlen(file_path) + 13];
  if (snprintf(relative_file_path, 255, "../Resources/%s", file_path) < 0)
  {
    alert(ERROR, "[RES ERROR] : FORMATTING STRING (SNPRINTF)!\nEXITING...");
    exit(ERROR_SNPRINTF);
  }
  FILE *file = fopen(relative_file_path, "r");
  if (!file) alert(INFO, "[RES ERROR] : UNABLE TO READ FROM FILE %s", relative_file_path);
  while (true)  // Get current line.
  {
    char line[128];
    int resource = fscanf(file, "%s", line);
    if (resource == EOF) break;

    if (strcmp(line, "v") == 0) load_vertices(file, mesh_s);  // Load vertex coordinates.
    if (strcmp(line, "f") == 0) load_indices(file, mesh_s);  // Load index coordinates.
    if (strcmp(line, "vt") == 0) load_textures(file, mesh_s);  // Load texture coordinates.
  }
  set_vertex_textures(mesh_s);  // Set Vector_2f texture coordinates for each appropriate vertex.
  if (mesh_s.texCoords.empty()) alert(ERROR, "[RES ERROR] : OBJECT FILE (.OBJ) FOR TEXTURE DATA (f) NOT FOUND!");
  if (mesh_s.vertices.empty()) alert(ERROR, "[RES ERROR] : OBJECT FILE (.OBJ) FOR VERTEX DATA (v) NOT FOUND!");
  if (mesh_s.indices.empty()) alert(ERROR, "[RES ERROR] : OBJECT FILE (.OBJ) FOR FACE DATA (f) NOT FOUND!");
  return mesh_s;
}

void load_vertices(FILE *file, res_loader_t &mesh_s)
{
  float x, y, z;
  if (fscanf(file, "%f %f %f\n", &x, &y, &z) == EOF)  // NOLINT
    alert(ERROR, "[RES ERROR] : LOADING VERTICES (v)");
  else
    mesh_s.vertices.emplace_back(Vertex(Vector_3f(x, y, z),
                                        Vector_2f(0, 0)));
}

void load_indices(FILE *file, res_loader_t &mesh_s)
{
  unsigned int indices[3];
  if (fscanf(file, "%u %u %u\n", &indices[0], &indices[1], &indices[2]) == EOF)  // NOLINT
    alert(ERROR, "[RES ERROR] : LOADING INDICES (f)");
  else mesh_s.indices.emplace_back(indices[0] - 1);
}

void load_textures(FILE *file, res_loader_t &mesh_s)
{
  float x = 0.0f, y = 0.0f;  // Texture positions for vector_2f.
  if (fscanf(file, "%f %f", &x, &y) == EOF)  // NOLINT
    alert(ERROR, "[RES ERROR] : LOADING INDICES (f)");  // Get next string after space.
  else mesh_s.texCoords.emplace_back(x, y);
}

void set_vertex_textures(res_loader_t &mesh_s)
{
  for (int i = 0; i < mesh_s.vertices.size(); i++) mesh_s.vertices[i].set_texCoord(mesh_s.texCoords[i]);
}



