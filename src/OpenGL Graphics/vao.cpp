//
// Created by nami on 2022-02-23.
//

#include <iostream>
#include "../../Include/OpenGL Graphics/vao.h"

Vao::Vao()
{
  printf("CREATING VAO...");
  glGenVertexArrays(1, &vao);
  printf("Done.\n");
}

Vao::~Vao()
{
  glDeleteVertexArrays(1, &vao);
  printf("DESTROYING VAO...\n");
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
void Vao::link_attrib(const GLuint type, int size, const GLsizei stride, void *offset) {
  glVertexAttribPointer(type, size, GL_FLOAT, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(type);
}
