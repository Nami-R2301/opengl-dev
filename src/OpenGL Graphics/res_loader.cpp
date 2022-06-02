//
// Created by nami on 5/20/22.
//
#include "res_loader.h"
#include "../Logs/logger.h"
#include <sstream>

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
  std::string line;
  std::string prefix;
  std::stringstream ss;

  // Add filename to path.
  char relative_file_path[strlen(file_path) + 13];
  if (snprintf(relative_file_path, 255, "../Resources/%s", file_path) < 0)
  {
    alert(ERROR, "ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...");
    exit(ERROR_SNPRINTF);
  }
  std::ifstream file_stream(relative_file_path);
  if (file_stream.fail()) alert(INFO, "[RES ERROR] : UNABLE TO READ FROM FILE %s", relative_file_path);
  res_loader_t mesh_s;
  while (std::getline(file_stream, line))  // Get current line.
  {
    ss.clear();
    ss.str(line);
    ss >> prefix;

    if (prefix == "v") load_vertices(ss, mesh_s);  // Load vertex coordinates.
    if (prefix == "f") load_indices(ss, line, mesh_s);  // Load index coordinates.
    if (prefix == "vt") load_textures(ss, mesh_s);  // Load texture coordinates.
  }
  set_vertex_textures(mesh_s);  // Set Vector_2f texture coordinates for each appropriate vertex.
  if (mesh_s.texCoords.empty())
    alert(ERROR,
          "ERROR : OBJECT FILE (.OBJ) FOR TEXTURE DATA (f) NOT FOUND!");
  if (mesh_s.vertices.empty())
    alert(ERROR,
          "ERROR : OBJECT FILE (.OBJ) FOR VERTEX DATA (v) NOT FOUND!");
  if (mesh_s.indices.empty())
    alert(ERROR,
          "ERROR : OBJECT FILE (.OBJ) FOR FACE DATA (f) NOT FOUND!");
  file_stream.close();
  return mesh_s;
}

void load_vertices(std::stringstream &ss, res_loader_t &mesh_s)
{
  float x = 0.0f, y = 0.0f, z = 0.0f;
  ss >> x >> y >> z;
  mesh_s.vertices.emplace_back(Vertex(Vector_3f(x, y, z), Vector_2f(0, 0)));
}

void load_indices(std::stringstream &ss, std::string &line, res_loader_t &mesh_s)
{
  GLuint temp_indices[3];
  if (line.size() <= 7)  // Only has vertex faces.
  {
    ss >> temp_indices[0] >> temp_indices[1] >> temp_indices[2];
    mesh_s.indices.emplace_back(temp_indices[0] - 1);
    mesh_s.indices.emplace_back(temp_indices[1] - 1);
    mesh_s.indices.emplace_back(temp_indices[2] - 1);
  } else  // Vertex/vertex texture/vertex normal (v/vt/vn).
  {
    char *faces = (char *) malloc(line.size());
    for (int i = 0; i < 3; i++)
    {
      ss >> faces;  // Get next string after space.
      char *ptr = strtok(faces, "/");  // Separate by delim.
      mesh_s.indices.emplace_back(strtof(ptr, nullptr) - 1);  // Obj indexing starts at 1, so -1.
    }
    free(faces);
  }
}

void load_textures(std::stringstream &ss, res_loader_t &mesh_s)
{
  float x, y;  // Texture positions for vector_2f.
  ss >> x >> y;
  mesh_s.texCoords.emplace_back(x, y);
}

void set_vertex_textures(res_loader_t &mesh_s)
{
  for (int i = 0; i < mesh_s.vertices.size(); i++) mesh_s.vertices[i].set_texCoord(mesh_s.texCoords[i]);
}



