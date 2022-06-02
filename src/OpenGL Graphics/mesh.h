//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_MESH_H
#define OPENGL_DEV_MESH_H

#include <vector>
#include "vertex.h"
#include "vertex_buffer.h"
#include "vertex_array_buffer.h"
#include "index_buffer.h"
#include "texture.h"
#include "../Logs/logger.h"

class Mesh
{
public:
  Mesh() = default;

  void setup_mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
                  const Buffer_layout &layout);
  void draw();
  void delete_buffers() const;

private:
  Vertex_buffer vbo;
  Vertex_array_buffer vao;
  Index_buffer ibo;
  Texture tex;
};

#endif //OPENGL_DEV_MESH_H
