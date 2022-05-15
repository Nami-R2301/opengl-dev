//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_VAO_H
#define OPENGL_DEV_VAO_H
#include <GLES3/gl3.h>
#include "vbo.h"

// Create vertex array to contain vertex objects to process.
class Vao {
public:
  Vao();

  ~Vao();

  void bind_vertex_array() const;

  static void link_attrib(GLuint index, int size, GLsizei stride, void *offset);

  static void unbind_vertex_array();

private:
  GLuint vao = 0;
};


#endif //OPENGL_DEV_VAO_H
