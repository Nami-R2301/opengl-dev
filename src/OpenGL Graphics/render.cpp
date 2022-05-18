//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/render.h"

static bool glfw_init = false;  // Flag to check glfw init status.

void Render::reset_bg()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear and change the back buffer color bit with our color.
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

void Render::init_graphics()
{
  //  glDebugMessageCallback(GLDebugMessageCallback, NULL);
  glfwSetErrorCallback(glfw_error_callback); // Set error callback for glfw calls.

  // Enable openGL error handling.
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);  // Calls to callback will be synchronous for debug breakpoints.
  glEnable(GL_DEBUG_OUTPUT);  // Enable debug output.
  if (glGetError() != 0) gl_error_callback(glGetError());  // check errors.

  // Init glfw library.
  output_on_screen("INITIALIZING GLFW...\t", INFO);
  glfwInit();
  glfw_init = true;
  printf("Done.\n");

  Color background_color;  // Default dark-mode-like color for background.
  glClearColor(background_color.get_red(), background_color.get_green(),
               background_color.get_blue(), background_color.get_alpha());

  glFrontFace(GL_CW); // Every shape drawn in clock-wise manner will be considered the FRONT face.
  if (glGetError() != 0) gl_error_callback(glGetError());  // check errors.
  glCullFace(GL_BACK); // The back side of shapes will NOT be drawn.
  if (glGetError() != 0) gl_error_callback(glGetError());  // check errors.
  glEnable(GL_CULL_FACE); // Don't render the back face of shapes since the camera won't see it.
  if (glGetError() != 0) gl_error_callback(glGetError());  // check errors.

  // Let OpenGL keep track of depth for shapes and auto determine if some shapes closer or further away from
  // the camera should take priority (drawn on top of other ones).
  glEnable(GL_DEPTH_TEST);
  if (glGetError() != 0) gl_error_callback(glGetError());  // check errors.

  //TODO: Depth clamp for later.

  // Let OpenGL do the exponential gamma correction for us so textures and colors don't appear as dark.
  glEnable(GL_FRAMEBUFFER_SRGB);
  if (glGetError() != 0) gl_error_callback(glGetError());  // check errors.
}

const char *Render::get_GL_version()
{
  return (const char *) (glGetString(GL_VERSION));
}

void Render::show_gl_info()
{
  // Get openGL and GLFW version.
  int num_ext;
  glGetIntegerv(GL_NUM_EXTENSIONS, &num_ext);
  char buffer[75];
  snprintf(buffer, 75, "Extensions available : %d\n", num_ext);
  output_on_screen(buffer);
  snprintf(buffer, 75, "Opengl version : %s\n", get_GL_version());
  output_on_screen(buffer);
  snprintf(buffer, 75, "GLFW Version : %s\n", glfwGetVersionString());
  output_on_screen(buffer);
}

void Render::glfw_error_callback(int error_code, const char *err_str)
{
  char print_buffer[256];
  snprintf(print_buffer, 256, "ERROR : %s\n", err_str);
  output_on_screen(print_buffer, ERROR);
  if (glfw_init) glfwTerminate();  // If glfw has been initialized.
  exit(error_code);
}

void Render::gl_error_callback(GLenum source)
{
  char _source[50];
  switch (source)
  {
    case GL_DEBUG_SOURCE_API:
      sprintf(_source, "API");
      break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      sprintf(_source, "WINDOW SYSTEM");
      break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      sprintf(_source, "SHADER COMPILER");
      break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
      sprintf(_source, "THIRD PARTY");
      break;

    case GL_DEBUG_SOURCE_APPLICATION:
      sprintf(_source, "APPLICATION");
      break;

    default:
      sprintf(_source, "UNKNOWN");
      break;
  }
  char print_buffer[256];
  snprintf(print_buffer, 256, "OpenGL error :\n%s ERROR", _source);
  output_on_screen(print_buffer, ERROR);
  exit((int) source);
}