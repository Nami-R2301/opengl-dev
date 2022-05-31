//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/mesh.h"

Mesh::Mesh() = default;

std::vector<GLuint> Mesh::get_indices() const
{
  return this->indices;
}

void Mesh::set_indices(const std::vector<GLuint> &indices_)
{
  this->indices = indices_;
}

void Mesh::set_tex_id(unsigned int tex_id_)
{
  this->tex = tex_id_;
}

void Mesh::setup_graphics(const Vertex *vertices, unsigned long size_)
{
  add_vbo();
  add_vertices(vertices, size_);
  add_vao();
  bind_vao();
  add_evo();
  bind_evo(get_indices());
  bind_tex();

  glEnableVertexAttribArray(0);  // layout (location = 0) (position).
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 35);  // check errors.
  glVertexAttribPointer(0, COUNT_VECTOR3D, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                        (void *) POSITION_OFFSET);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 38);  // check errors.

  glEnableVertexAttribArray(1);  // layout (location = 1) (color).
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 41);  // check errors.
  glVertexAttribPointer(1, COUNT_COLOR, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                        (void *) (COLOR_OFFSET));
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 44);  // check errors.

  glEnableVertexAttribArray(2);  // layout (location = 2) (texCoord).
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 47);  // check errors.
  glVertexAttribPointer(2, COUNT_VECTOR2D, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                        (void *) (TEXTURE_OFFSET));
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 50);  // check errors.

  unbind_tex();
  unbind_vao();
  unbind_vbo();
  unbind_evo();
}

void Mesh::add_vbo()
{
  Logger::alert(INFO, "CREATING VBO...");
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex_source data.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 62);  // check errors.
}

void Mesh::add_vao()
{
  Logger::alert(INFO, "CREATING VAO...");
  glGenVertexArrays(1, &vao);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 70);  // check errors.
}

void Mesh::add_evo()
{
  Logger::alert(INFO, "CREATING EVO...");
  glGenBuffers(1, &evo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 78);  // check errors.
}

void Mesh::bind_vbo() const
{
  Logger::alert(INFO, "BINDING VBO...");
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 86);  // check errors.
}

void Mesh::bind_vao() const
{
  glBindVertexArray(vao);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 93);  // check errors.
}

void Mesh::bind_evo(const std::vector<GLuint> &indices_) const
{
  Logger::alert(INFO, "BINDING EVO...");
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 100);  // check errors.
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (indices_.size() * sizeof(int)),
               indices_.data(), GL_STATIC_DRAW);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 103);  // check errors.
}

void Mesh::bind_tex(unsigned int slot_) const
{
  glActiveTexture(GL_TEXTURE0 + slot_);  // Set our active texture slot.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 110);  // check errors.
  glBindTexture(GL_TEXTURE_2D, this->tex);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 112);  // check errors.
}

void Mesh::add_vertices(const Vertex *vertices, unsigned long size_)
{
  this->size = (int) size_;
  bind_vbo();
  glBufferData(GL_ARRAY_BUFFER, this->size, vertices, GL_STATIC_DRAW); // For vbo.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 120);  // check errors.
}

void Mesh::unbind_tex()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::unbind_vbo()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 131);  // check errors.
}

void Mesh::unbind_vao()
{
  glBindVertexArray(0);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 137);  // check errors.
}

void Mesh::unbind_evo()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 143);  // check errors.
}

void Mesh::draw() const
{
  bind_vao();
  bind_tex();
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 150);  // check errors.
  glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr); // Draw from vertex_source arrays.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 152);  // check errors.
}

void Mesh::cleanup()
{
  //Delete vbo.
  Logger::alert(INFO, "DESTROYING VBO...");
  glDeleteBuffers(1, &vbo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 160);  // check errors.
  // Delete vao.
  Logger::alert(INFO, "DESTROYING VAO...");
  glDeleteVertexArrays(1, &vao);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 165);  // check errors.
  //Delete evo.
  Logger::alert(INFO, "DESTROYING EVO...");
  glDeleteBuffers(1, &evo);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 170);  // check errors.
  //Delete texture.
  Logger::alert(INFO, "DESTROYING TEXTURE...");
  glDeleteTextures(1, &tex);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "MESH.CPP", 160);  // check errors.
}
