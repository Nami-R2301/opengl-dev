//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_RENDER_H
#define OPENGL_DEV_RENDER_H

#include "GLFW/glfw3.h"
#include "color.h"

typedef struct gl_version_s
{
  int major;
  int minor;
  int rev;
} gl_version_t;

class Render
{
public:
  static void render_screen();
  static void init_graphics();
  static gl_version_t get_GL_version();
};

#endif //OPENGL_DEV_RENDER_H
