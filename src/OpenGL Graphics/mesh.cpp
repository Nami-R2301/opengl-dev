//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/mesh.h"

Mesh::Mesh() = default;

void Mesh::add_vbo()
{
  output_on_screen("CREATING VBO...\t");
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex data.
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  output_on_screen("Done.\n", INFO, true);
}

void Mesh::add_vao()
{
  output_on_screen("CREATING VAO...\t");
  glGenVertexArrays(1, &vao);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  output_on_screen("Done.\n", INFO, true);
}

void Mesh::add_evo()
{
  output_on_screen("CREATING EVO...\t");
  glGenBuffers(1, &evo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  output_on_screen("Done.\n", INFO, true);
}

void Mesh::bind_vbo() const
{
  output_on_screen("BINDING VBO...\t");
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  output_on_screen("Done.\n", INFO, true);
}

void Mesh::bind_vao() const
{
  glBindVertexArray(vao);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

void Mesh::bind_evo() const
{
  output_on_screen("BINDING EVO...\t");
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // For evo.
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  output_on_screen("Done.\n", INFO, true);
}

void Mesh::add_vertices(const Vertex *vertices, unsigned long size_)
{
  this->size = (int) size_;
  bind_vbo();
  glBufferData(GL_ARRAY_BUFFER, this->size, vertices, GL_STATIC_DRAW); // For vbo.
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

void Mesh::draw() const
{
  bind_vao();
  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
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
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  glEnableVertexAttribArray(0);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (4 * sizeof(float)));
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  glEnableVertexAttribArray(1);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.

  unbind_vao();
  unbind_vbo();
  unbind_evo();
}

void Mesh::unbind_vbo()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

void Mesh::unbind_vao()
{
  glBindVertexArray(0);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

void Mesh::unbind_evo()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

void Mesh::cleanup()
{
  //Delete vbo.
  output_on_screen("DESTROYING VBO...\t");
  glDeleteBuffers(1, &vbo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  printf("Done.\n");
  // Delete vao.
  output_on_screen("DESTROYING VAO...\t");
  glDeleteVertexArrays(1, &vao);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  printf("Done.\n");
  //Delete evo.
  output_on_screen("DESTROYING EVO...\t");
  glDeleteBuffers(1, &evo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  output_on_screen("Done.\n", INFO, true);
}
