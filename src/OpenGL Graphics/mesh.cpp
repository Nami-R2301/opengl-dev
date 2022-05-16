//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/mesh.h"

Mesh::Mesh() = default;

void Mesh::add_vbo()
{
  printf("CREATING VBO...\t");
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex data.
  printf("Done.\n");
}

void Mesh::add_vao()
{
  printf("CREATING VAO...\t");
  glGenVertexArrays(1, &vao);
  printf("Done.\n");
}

void Mesh::add_evo()
{
  printf("CREATING EVO...\t");
  glGenBuffers(1, &evo);
  printf("Done.\n");
}

void Mesh::bind_vbo() const
{
  printf("BINDING VBO...\t");
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  printf("Done.\n");
}

void Mesh::bind_vao() const
{
  glBindVertexArray(vao);
}

void Mesh::bind_evo() const
{
  printf("BINDING EVO...\t");
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // For evo.
  printf("Done.\n");
}

void Mesh::add_vertices(const Vertex *vertices, unsigned long size_)
{
  this->size = (int) size_;
  bind_vbo();
  glBufferData(GL_ARRAY_BUFFER, this->size, vertices, GL_STATIC_DRAW); // For vbo.
}

void Mesh::draw() const
{
  bind_vao();
  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.
}

void Mesh::setup_graphics(const Vertex *vertices, unsigned long size_)
{
  add_vbo();
  add_vertices(vertices, size_);
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

void Mesh::cleanup()
{
  //Delete vbo.
  printf("DESTROYING VBO...\t");
  glDeleteBuffers(1, &vbo);
  printf("Done.\n");
  // Delete vao.
  printf("DESTROYING VAO...\t");
  glDeleteVertexArrays(1, &vao);
  printf("Done.\n");
  //Delete evo.
  printf("DESTROYING EVO...\t");
  glDeleteBuffers(1, &evo);
  printf("Done.\n");
}
