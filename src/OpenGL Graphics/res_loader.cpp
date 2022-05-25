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
          indices.emplace_back(strtof(ptr, nullptr) - 1);  // get first index only.
        }
        free(faces);
      }
    }
  }
  free(c_line);
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



