//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/mesh.h"

Mesh::Mesh()
{
  this->size = 0;
  printf("CREATING EMPTY VBO...\t");
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex data.
  printf("Done.\n");
}

void Mesh::add_vertices(const std::vector<Vertex> &vertices)
{
  auto *vertices_c = const_cast<Vertex *>(vertices.data());
  this->size = int(vertices.size());

  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, this->size, vertices_c, GL_STATIC_DRAW);
}

void Mesh::draw() const
{
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * 4, nullptr);
  glDrawArrays(GL_TRIANGLES, 0, size); // Draw from vertex arrays.
  glDisableVertexAttribArray(0);
}
