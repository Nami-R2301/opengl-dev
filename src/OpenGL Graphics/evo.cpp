//
// Created by nami on 2022-02-23.
//

#include "../../Include/OpenGL Graphics//evo.h"

Evo::Evo(GLuint* indices, GLsizeiptr size)
{
  glGenBuffers(1, &evo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

Evo::~Evo()
{
  glDeleteBuffers(1, &evo);
}

void Evo::bind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo);
}

void Evo::unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}