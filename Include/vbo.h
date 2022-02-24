//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_VBO_H
#define OPENGL_DEV_VBO_H
#include <GLES3/gl3.h>
#include "../Include/vertex.h"

class Vbo
{
public:
  Vbo(Vertex* vertices, GLsizeiptr size);
  ~Vbo();
  void bind_buffer() const;
  void bind_data(const void* vertices, long data_length);
  void unbind();
  [[nodiscard]] GLuint get_value() const;

private:
  GLuint vbo = 0;
};


#endif //OPENGL_DEV_VBO_H
