//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_RENDER_H
#define OPENGL_DEV_RENDER_H

#include "GLFW/glfw3.h"
#include <GLES3/gl3.h>
#include "color.h"
#include <cmath>
#include "../Logs/logger.h"

#define GL_ERROR 0
// Macro to log openGL errors in an efficient and clean way.
#define gl_call(x) Render::gl_clear_errors(); x; Render::gl_error_callback(glGetError(), #x, __FILE__, __LINE__)

class Render
{
public:
  static void gl_clear_errors();
  static void init_graphics();
  static const char *get_GL_version();
  static void set_textures(bool enabled);
  static void show_gl_info();
  static void reset_bg();
  static void set_clear_color(const Color &color);
  static void glfw_error_callback(int error_code, const char *err_str);
  static void gl_error_callback(GLenum source, const char *function_name,
                                const char *source_file, unsigned int line_number);
};

#endif //OPENGL_DEV_RENDER_H
