//
// Created by nami on 5/14/22.
//

#include "../../Include/OpenGL Graphics/render.h"

static bool glfw_init = false;  // Flag to check glfw prepare_mesh status.

void Render::gl_clear_errors()
{
  while (glGetError());  // Clear all previous openGL errors before polling the next one.
}

void Render::reset_bg()
{
  gl_call(
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // Clear and change the back buffer color bit with our color.
}

void Render::set_clear_color(const Color &color)
{
  gl_call(glClearColor(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha()));
}

void Render::set_textures(bool enabled)
{
  if (enabled) glEnable(GL_TEXTURE_2D);
  else glDisable(GL_TEXTURE_2D);
}

void Render::init_graphics()
{
  //  glDebugMessageCallback(GLDebugMessageCallback, NULL);
  glfwSetErrorCallback(glfw_error_callback); // Set error callback for glfw calls.

  // Enable openGL error handling.
  gl_call(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));  // Calls to callback will be synchronous for debug breakpoints.
  gl_call(glEnable(GL_DEBUG_OUTPUT));  // Enable debug output.
  set_textures(true);  // Enable textures.

  // Init glfw library.
  Logger::alert(INFO, "INITIALIZING GLFW...");
  glfwInit();
  glfw_init = true;

  Color background_color;  // Default dark-mode-like color for background.
  gl_call(glClearColor(background_color.get_red(), background_color.get_green(),
                       background_color.get_blue(), background_color.get_alpha()));

  gl_call(glFrontFace(GL_CW)); // Every shape drawn in clock-wise manner will be considered the FRONT face.
  gl_call(glCullFace(GL_BACK)); // The back side of shapes will NOT be drawn.
  gl_call(glDisable(GL_CULL_FACE)); // Don't render the back face of shapes since the camera won't see it.

  // Let OpenGL keep track of depth for shapes and auto determine if some shapes closer or further away from
  // the camera should take priority (drawn on top of other ones).
  gl_call(glEnable(GL_DEPTH_TEST));

  //TODO: Depth clamp for later.

  // Let OpenGL do the exponential gamma correction for us so textures and colors don't appear as dark.
  gl_call(glEnable(GL_FRAMEBUFFER_SRGB));
}

const char *Render::get_GL_version()
{
  return (const char *) (glGetString(GL_VERSION));
}

void Render::show_gl_info()
{
  Logger::alert(INFO, "FETCHING OPENGL AND GLFW INFO");
  // Get openGL and GLFW version.
  int num_ext;
  gl_call(glGetIntegerv(GL_NUM_EXTENSIONS, &num_ext));
  Logger::alert(INFO, "Extensions available : %d", num_ext);
  Logger::alert(INFO, "Opengl version : %s", get_GL_version());
  Logger::alert(INFO, "GLFW Version : %s", glfwGetVersionString());
}

void Render::glfw_error_callback(int error_code, const char *err_str)
{
  Logger::alert(ERROR, "ERROR : %s", err_str);
  if (glfw_init) glfwTerminate();  // If glfw has been initialized.
  exit(error_code);
}

void Render::gl_error_callback(GLenum source, const char *function_name,
                               const char *source_file, unsigned int line_number)
{
  char _source[50];
  if (source != GL_NO_ERROR)
  {
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

      case GL_INVALID_OPERATION:
        sprintf(_source, "INVALID OPENGL OPERATION FOR UNIFORM");
        break;

      default:
        sprintf(_source, "UNKNOWN");
        break;
    }
    Logger::alert(ERROR, "OPENGL ERROR IN FILE %s, IN FUNCTION %s, AT LINE %d :\n%s ERROR",
                  source_file, function_name, line_number, _source);
    exit((int) source);
  }
}
