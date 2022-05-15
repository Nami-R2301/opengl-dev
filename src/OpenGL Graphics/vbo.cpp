//
// Created by nami on 2022-02-23.
//

#include <iostream>
#include "../../Include/OpenGL Graphics/vbo.h"

Vbo::Vbo()
{
  printf("CREATING EMPTY VBO...\t");
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex data.
  printf("Done.\n");
}

Vbo::Vbo(const Vertex *vertices, const GLsizeiptr size)
{
  printf("CREATING VBO WITH DATA AND SIZE...\t");
  glGenBuffers(1, &vbo); // Create empty buffer for our vertex data.
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  printf("Done.\n");
}

Vbo::~Vbo()
{
  glDeleteBuffers(1, &vbo);
  std::cout << "DESTROYING VBO...\n";
}

void Vbo::bind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
}

// Unbind our vertex objects to prevent further usage of these buffers.
void Vbo::unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

[[maybe_unused]] GLuint Vbo::get_value() const
{
  return vbo;
}
