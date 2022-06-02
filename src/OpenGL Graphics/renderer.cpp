//
// Created by nami on 5/14/22.
//

#include "renderer.h"
#include "../Logs/logger.h"

static bool glfw_init = false;  // Flag to check glfw prepare_mesh status.

void gl_clear_errors()
{
  while (glGetError());  // Clear all previous openGL errors before polling the next one.
}

void reset_bg()
{
  gl_call(
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)); // Clear and change the back buffer color bit with our color.
}

void set_clear_color(const Color &color)
{
  gl_call(glClearColor(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha()));
}

void set_textures(bool enabled)
{
  if (enabled) glEnable(GL_TEXTURE_2D);
  else glDisable(GL_TEXTURE_2D);
}

void init_graphics()
{
  //  glDebugMessageCallback(GLDebugMessageCallback, NULL);
  glfwSetErrorCallback(glfw_error_callback); // Set error callback for glfw calls.

  // Enable openGL error handling.
  gl_call(glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS));  // Calls to callback will be synchronous for debug breakpoints.
  gl_call(glEnable(GL_DEBUG_OUTPUT));  // Enable debug output.
  set_textures(true);  // Enable textures.

  // Init glfw library.
  alert(INFO, "INITIALIZING GLFW...");
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

const char *get_GL_version()
{
  return (const char *) (glGetString(GL_VERSION));
}

void show_gl_info()
{
  alert(INFO, "FETCHING OPENGL AND GLFW INFO");
  // Get openGL and GLFW version.
  int num_ext;
  gl_call(glGetIntegerv(GL_NUM_EXTENSIONS, &num_ext));
  alert(INFO, "Extensions available : %d", num_ext);
  alert(INFO, "Opengl version : %s", get_GL_version());
  alert(INFO, "GLFW Version : %s", glfwGetVersionString());
}

void add_vbo(const unsigned int *vbo_id)
{
  alert(INFO, "CREATING VBO...");
  gl_call(glGenBuffers(1, (GLuint *) vbo_id)); // Create empty buffer for our vertex_source data.
}

void add_vao(const unsigned int *vao_id)
{
  alert(INFO, "CREATING VAO...");
  gl_call(glGenVertexArrays(1, (GLuint *) vao_id));
}

void add_ibo(const unsigned int *ibo_id)
{
  alert(INFO, "CREATING EVO...");
  gl_call(glGenBuffers(1, (GLuint *) ibo_id));
}

void bind_vbo(const unsigned int *vbo_id)
{
  alert(INFO, "BINDING VBO...");
  gl_call(glBindBuffer(GL_ARRAY_BUFFER, *vbo_id));
}

void bind_vao(const unsigned int *vao_id)
{
  gl_call(glBindVertexArray(*vao_id));
}

void bind_ibo(const unsigned int *ibo_id)
{
  alert(INFO, "BINDING EVO...");
  gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo_id));
}

void bind_tex(const unsigned int *tex_id, unsigned int slot_)
{
  gl_call(glActiveTexture(GL_TEXTURE0 + slot_));  // Set our active texture slot.
  gl_call(glBindTexture(GL_TEXTURE_2D, *tex_id));
}

void unbind_tex()
{
  gl_call(glBindTexture(GL_TEXTURE_2D, 0));
}

void unbind_vbo()
{
  gl_call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void unbind_vao()
{
  gl_call(glBindVertexArray(0));
}

void unbind_ibo()
{
  gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void delete_vbo(const unsigned int *vbo)
{
  alert(INFO, "DESTROYING VBO...");
  gl_call(glDeleteBuffers(1, vbo));
}

void delete_vao(const unsigned int *vao)
{
  alert(INFO, "DESTROYING VAO...");
  gl_call(glDeleteVertexArrays(1, vao));
}

void delete_ibo(const unsigned int *ibo)
{
  alert(INFO, "DESTROYING IBO...");
  gl_call(glDeleteBuffers(1, ibo));
}

void delete_tex(const unsigned int *tex)
{
  alert(INFO, "DESTROYING TEXTURE...");
  gl_call(glDeleteTextures(1, tex));
}

void glfw_error_callback(int error_code, const char *err_str)
{
  alert(ERROR, "[GLFW ERROR] : %s", err_str);
  if (glfw_init) glfwTerminate();  // If glfw has been initialized.
  exit(error_code);
}

void gl_error_callback(GLenum source, const char *function_name,
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
        sprintf(_source, "INVALID OPENGL OPERATION");
        break;

      default:
        sprintf(_source, "UNKNOWN");
        break;
    }
    alert(ERROR, "[OPENGL ERROR]\nIN FILE %s, IN FUNCTION %s, AT LINE %d :\n%s",
          source_file, function_name, line_number, _source);
    exit((int) source);
  }
}
