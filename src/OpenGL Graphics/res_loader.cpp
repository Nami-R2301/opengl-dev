//
// Created by nami on 5/20/22.
//
#include "../../Include/OpenGL Graphics/res_loader.h"

Resource_loader::Resource_loader(const char *file_path)
{
  this->file_stream = std::ifstream(file_path);
}

Mesh Resource_loader::load_obj_data()
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
    char *result = strncpy(c_line, ss.str().c_str(), ss.str().size());  // Convert to c-like strings for strtok.
    if (result == nullptr) Logger::alert("ERROR WHILE SPLITING LINE TO BUFFER (STRTOK)!\nEXITING...\n", ERROR);

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
        while (ss)  // Split with spaces.
        {
          char *current_pos = strtok(result, " ");
          current_pos = strtok(nullptr, " ");  // Skip prefix.
          current_pos = strtok(current_pos, "/");
          while (current_pos != nullptr)
          {
            indices.emplace_back(strtof(current_pos, nullptr));
            current_pos = strtok(nullptr, "/");
          }
          current_pos = strtok(current_pos, " ");
        }
      }
    }
  }
  if (vertices.empty()) Logger::alert("ERROR : OBJECT FILE (.OBJ) FOR VERTEX DATA (v) NOT FOUND!\n", ERROR);
  if (indices.empty()) Logger::alert("ERROR : OBJECT FILE (.OBJ) FOR FACE DATA (f) NOT FOUND!\n", ERROR);
  Mesh mesh;
  mesh.set_indices(indices);
  mesh.setup_graphics(vertices.data(), VERTEX_SIZE * vertices.size());
  return mesh;
}

Resource_loader::~Resource_loader()
{
  this->file_stream.close();
}

const std::vector<GLuint> &Resource_loader::get_face_indices()
{
  return this->indices;
}

const std::vector<Vertex> &Resource_loader::get_vertices()
{
  return this->vertices;
}



