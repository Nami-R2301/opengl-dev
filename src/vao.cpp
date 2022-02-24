//
// Created by nami on 2022-02-23.
//

#include "../Include/vao.h"

Vao::Vao()
{
  glGenVertexArrays(1, &vao);
}

Vao::~Vao()
{
  glDeleteVertexArrays(1, &vao);
}

// Make the VAO the current Vertex Array Object by binding it
void Vao::bind_vertex_array() const
{
  glBindVertexArray(vao);
}

// Unbind our vertex objects to prevent further usage of these buffers.
void Vao::unbind_vertex_array()
{
  glBindVertexArray(0);
}

// Arguments serve to specify the number, type and stride (number of bytes to 'hop' between data).
void Vao::link_attrib(Vbo& vbo, const GLuint type, int size, const GLsizei stride, void* offset)
{
  vbo.bind_buffer();
  glVertexAttribPointer(type, size, GL_FLOAT, GL_FALSE, stride, nullptr);
  glEnableVertexAttribArray(type);
  vbo.unbind();
}
