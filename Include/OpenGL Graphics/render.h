//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_RENDER_H
#define OPENGL_DEV_RENDER_H

#include "GLFW/glfw3.h"
#include "color.h"
#include <cmath>
#include "../../Include/Logs/logger.h"

class Render
{
public:
  static void init_graphics();
  static const char *get_GL_version();
  static void show_gl_info();
  static void reset_bg();
  static void glfw_error_callback(int error_code, const char *err_str);
  static void gl_error_callback(GLenum source);
};

#endif //OPENGL_DEV_RENDER_H
