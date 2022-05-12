//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_VBO_H
#define OPENGL_DEV_VBO_H
#include <GLES3/gl3.h>
#include "../Include/vertex.h"

class Vbo {
public:
  Vbo();
  Vbo(const Vertex *vertices, GLsizeiptr size);
  ~Vbo();
  static void unbind();
  [[maybe_unused]] [[nodiscard]] GLuint get_value() const;
private:
  GLuint vbo = 0;
};


#endif //OPENGL_DEV_VBO_H
