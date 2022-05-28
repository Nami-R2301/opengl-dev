//
// Created by nami on 5/20/22.
//
#include "../../Include/OpenGL Graphics/res_loader.h"

Resource_loader::Resource_loader(const char *file_path)
{
  // Add filename to path.
  char relative_file_path[255];
  if (snprintf(relative_file_path, 255, "../Resources/%s", file_path) < 0)
  {
    Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
    exit(ERROR_SNPRINTF);
  }
  this->file_stream = std::ifstream(relative_file_path);
}

std::string Resource_loader::load_shader_source(const char *file_path)
{
  // Add filename to path.
  char relative_file_path[255];
  if (snprintf(relative_file_path, 255, "../Resources/Shaders/%s", file_path) < 0)
  {
    Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
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

Texture Resource_loader::load_texture_file(const char *file_path)
{
  Logger::alert("LOADING TEXTURE...\t");
  Texture tex = Texture(file_path);
  Logger::alert("Done.\n", INFO, true);
  return tex;
}

void Resource_loader::load_mesh()
{
  std::string line;
  std::string prefix;
  std::stringstream ss;

  while (std::getline(this->file_stream, line))  // Get current line.
  {
    ss.clear();
    ss.str(line);
    ss >> prefix;

    if (prefix == "v") load_vertices(ss);  // Load vertex coordinates.
    if (prefix == "f") load_indices(ss, line);  // Load index coordinates.
    if (prefix == "vt") load_textures(ss);  // Load texture coordinates.
  }
  set_vertex_textures();  // Set Vector_2f texture coordinates for each appropriate vertex.
  if (texCoords.empty()) Logger::alert("ERROR : OBJECT FILE (.OBJ) FOR TEXTURE DATA (f) NOT FOUND!\n", ERROR);
  if (vertices.empty()) Logger::alert("ERROR : OBJECT FILE (.OBJ) FOR VERTEX DATA (v) NOT FOUND!\n", ERROR);
  if (indices.empty()) Logger::alert("ERROR : OBJECT FILE (.OBJ) FOR FACE DATA (f) NOT FOUND!\n", ERROR);
}

void Resource_loader::load_vertices(std::stringstream &ss)
{
  float x = 0.0f, y = 0.0f, z = 0.0f;
  ss >> x >> y >> z;
  vertices.emplace_back(Vertex(Vector_3f(x, y, z), Vector_2f(0, 0)));
}

void Resource_loader::load_indices(std::stringstream &ss, std::string &line)
{
  GLuint temp_indices[3];
  if (line.size() <= 7)  // Only has vertex faces.
  {
    ss >> temp_indices[0] >> temp_indices[1] >> temp_indices[2];
    indices.emplace_back(temp_indices[0] - 1);
    indices.emplace_back(temp_indices[1] - 1);
    indices.emplace_back(temp_indices[2] - 1);
  } else  // Vertex/vertex texture/vertex normal (v/vt/vn).
  {
    char *faces = (char *) malloc(line.size());
    for (int i = 0; i < 3; i++)
    {
      ss >> faces;  // Get next string after space.
      char *ptr = strtok(faces, "/");  // Separate by delim.
      indices.emplace_back(strtof(ptr, nullptr) - 1);  // Obj indexing starts at 1, so -1.
    }
    free(faces);
  }
}

void Resource_loader::load_textures(std::stringstream &ss)
{
  float x, y;  // Texture positions for vector_2f.
  ss >> x >> y;
  this->texCoords.emplace_back(x, y);
}

const std::vector<Vertex> &Resource_loader::get_vertices() const
{
  return vertices;
}

void Resource_loader::set_vertex_textures()
{
  for (int i = 0; i < vertices.size(); i++) this->vertices[i].set_texCoord(this->texCoords[i]);
}

const std::vector<GLuint> &Resource_loader::get_indices() const
{
  return indices;
}

Resource_loader::~Resource_loader()
{
  this->file_stream.close();
}



