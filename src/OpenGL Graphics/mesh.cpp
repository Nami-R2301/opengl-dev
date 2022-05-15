//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/mesh.h"

Mesh::Mesh() = default;

void Mesh::add_vbo()
{
  printf("CREATING EMPTY VBO...\t");
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex data.
  printf("Done.\n");
}

void Mesh::add_vao()
{
  printf("CREATING EMPTY VAO...\t");
  glGenVertexArrays(1, &vao);
  printf("Done.\n");
}

void Mesh::add_evo()
{
  printf("CREATING EMPTY EVO...\t");
  glGenBuffers(1, &evo);
  printf("Done.\n");
}

void Mesh::bind_vbo() const
{
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

void Mesh::bind_vao() const
{
  glBindVertexArray(vao);
}

void Mesh::bind_evo() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // For evo.
}

void Mesh::add_vertices(const std::vector <Vertex> &vertices)
{
  auto *vertices_c = const_cast<Vertex *>(vertices.data());
  this->size = int(vertices.size());

  bind_vbo();
  glBufferData(GL_ARRAY_BUFFER, this->size, vertices_c, GL_STATIC_DRAW); // For vbo.
}

void Mesh::draw() const
{
  bind_vao();
  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.
}

void Mesh::setup_graphics(const std::vector <Vertex> &vertices)
{
  add_vbo();
  add_vertices(vertices);
  add_vao();
  bind_vao();
  add_evo();
  bind_evo();

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) nullptr);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (4 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unbind_vao();
  unbind_vbo();
  unbind_evo();
}

void Mesh::unbind_vbo()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::unbind_vao()
{
  glBindVertexArray(0);
}

void Mesh::unbind_evo()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
