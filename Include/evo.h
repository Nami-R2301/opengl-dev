//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_EVO_H
#define OPENGL_DEV_EVO_H
#include <GLES3/gl3.h>

class Evo
{
public:
  Evo(GLuint* indices, GLsizeiptr size);
  ~Evo();
  void bind() const;
  void unbind();

private:
  GLuint evo = 0;
};


#endif //OPENGL_DEV_EVO_H
