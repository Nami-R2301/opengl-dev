//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_PROGRAM_H
#define OPENGL_DEV_PROGRAM_H
#include <GLES3/gl3.h>
#include <vector>
#include "../Include/shader.h"

class Program
{
public:
  Program();
  ~Program();
  void attach(const Shader&) const;
  void link() const;
  void activate() const;
  [[nodiscard]] GLuint get_program() const;

private:
  GLuint program = 0;
};


#endif //OPENGL_DEV_PROGRAM_H
