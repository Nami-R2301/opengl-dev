//
// Created by nami on 2022-02-23.
//

#include "../Include/vbo.h"

Vbo::Vbo(const Vertex* vertices, const GLsizeiptr size)
{
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex data.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Vbo::~Vbo()
{
  glDeleteBuffers(1, &vbo);
}

void Vbo::bind_buffer() const
{
  glBindBuffer(GL_ARRAY_BUFFER,vbo); // Bind it to an array containing multiple VBOs.
}

void Vbo::bind_data(const void *vertices, long data_length)
{
  glBufferData(GL_ARRAY_BUFFER, data_length, vertices, GL_STATIC_DRAW); // Specify the data.
}

// Unbind our vertex objects to prevent further usage of these buffers.
void Vbo::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Vbo::get_value() const
{
  return vbo;
}
