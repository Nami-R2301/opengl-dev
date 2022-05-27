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

Texture Resource_loader::load_texture(const char *file_path)
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
  GLuint temp_indices[3];
  std::stringstream ss;
  char *c_line = (char *) malloc(line.size());
  float x, y, z;  // Positions for vector_3f.
  while (std::getline(this->file_stream, line))  // Get current line.
  {
    ss.clear();
    ss.str(line);
    ss >> prefix;

    if (prefix == "v") // Vertex position
    {
      ss >> x >> y >> z;
      vertices.emplace_back(Vector_3f(x, y, z), Color(1.0f, 1.0f, 1.0f, 1.0f));
    } else if (prefix == "f") // Vertex position
    {
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
  }
  free(c_line);
  if (vertices.empty()) Logger::alert("ERROR : OBJECT FILE (.OBJ) FOR VERTEX DATA (v) NOT FOUND!\n", ERROR);
  if (indices.empty()) Logger::alert("ERROR : OBJECT FILE (.OBJ) FOR FACE DATA (f) NOT FOUND!\n", ERROR);
}

Resource_loader::~Resource_loader()
{
  this->file_stream.close();
}

std::vector<Vertex> Resource_loader::load_vertices() const
{
  return this->vertices;
}

std::vector<GLuint> Resource_loader::load_indices() const
{
  return this->indices;
}



