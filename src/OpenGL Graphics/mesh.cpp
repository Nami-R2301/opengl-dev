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

  gl_call(glEnableVertexAttribArray(0));  // layout (location = 0) (position).
  gl_call(glVertexAttribPointer(0, COUNT_VECTOR3D, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                                (void *) (POSITION_OFFSET)));

  gl_call(glEnableVertexAttribArray(1));  // layout (location = 1) (color).
  gl_call(glVertexAttribPointer(1, COUNT_COLOR, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                                (void *) (COLOR_OFFSET)));

  gl_call(glEnableVertexAttribArray(2));  // layout (location = 2) (texCoord).
  gl_call(glVertexAttribPointer(2, COUNT_VECTOR2D, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
                                (void *) (TEXTURE_OFFSET)));

  unbind_tex();
  unbind_vao();
  unbind_vbo();
  unbind_evo();
}

void Mesh::add_vbo()
{
  Logger::alert(INFO, "CREATING VBO...");
  gl_call(glGenBuffers(1, &vbo)); // Create empty buffer for our vertex_source data.
}

void Mesh::add_vao()
{
  Logger::alert(INFO, "CREATING VAO...");
  gl_call(glGenVertexArrays(1, &vao));
}

void Mesh::add_evo()
{
  Logger::alert(INFO, "CREATING EVO...");
  gl_call(glGenBuffers(1, &evo));
}

void Mesh::bind_vbo() const
{
  Logger::alert(INFO, "BINDING VBO...");
  gl_call(glBindBuffer(GL_ARRAY_BUFFER, this->vbo));
}

void Mesh::bind_vao() const
{
  gl_call(glBindVertexArray(vao));
}

void Mesh::bind_evo(const std::vector<GLuint> &indices_) const
{
  Logger::alert(INFO, "BINDING EVO...");
  gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo));
  gl_call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (long) (indices_.size() * sizeof(int)),
                       indices_.data(), GL_STATIC_DRAW));
}

void Mesh::bind_tex(unsigned int slot_) const
{
  gl_call(glActiveTexture(GL_TEXTURE0 + slot_));  // Set our active texture slot.
  gl_call(glBindTexture(GL_TEXTURE_2D, this->tex));
}

void Mesh::add_vertices(const Vertex *vertices, unsigned long size_)
{
  this->size = (int) size_;
  bind_vbo();
  gl_call(glBufferData(GL_ARRAY_BUFFER, this->size, vertices, GL_STATIC_DRAW)); // For vbo.
}

void Mesh::unbind_tex()
{
  gl_call(glBindTexture(GL_TEXTURE_2D, 0));
}

void Mesh::unbind_vbo()
{
  gl_call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Mesh::unbind_vao()
{
  gl_call(glBindVertexArray(0));
}

void Mesh::unbind_evo()
{
  gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Mesh::draw() const
{
  bind_vao();
  bind_tex();
  gl_call(
      glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr)); // Draw from vertex_source arrays.
}

void Mesh::cleanup()
{
  //Delete vbo.
  Logger::alert(INFO, "DESTROYING VBO...");
  gl_call(glDeleteBuffers(1, &vbo));
  // Delete vao.
  Logger::alert(INFO, "DESTROYING VAO...");
  gl_call(glDeleteVertexArrays(1, &vao));
  //Delete evo.
  Logger::alert(INFO, "DESTROYING EVO...");
  gl_call(glDeleteBuffers(1, &evo));
  //Delete texture.
  Logger::alert(INFO, "DESTROYING TEXTURE...");
  gl_call(glDeleteTextures(1, &tex));
}
