//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_PROGRAM_H
#define OPENGL_DEV_PROGRAM_H

#include "GLFW/glfw3.h"
#include <cmath>
#include <vector>
#include "../Include/shader.h"
#include "../Include/color.h"

class Program
{
public:
  Program();

  ~Program();

  void attach(const Shader &) const;

  void link() const;

  void validate() const;

  void activate() const;

  void update_scale(float) const;

  void update_color(const Color &) const;

  [[nodiscard]] GLuint get_program() const;

private:
  GLuint program = 0;
};


#endif //OPENGL_DEV_PROGRAM_H
