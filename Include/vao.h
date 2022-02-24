//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_VAO_H
#define OPENGL_DEV_VAO_H
#include <GLES3/gl3.h>
#include "vbo.h"

// Create vertex array to contain vertex objects to process.
class Vao
{
public:
  Vao();
  ~Vao();
  void bind_vertex_array() const;
  void link_attrib(Vbo& vbo, GLuint index, int size, GLsizei stride, void* offset);
  void unbind_vertex_array();

private:
  GLuint vao = 0;
};


#endif //OPENGL_DEV_VAO_H
