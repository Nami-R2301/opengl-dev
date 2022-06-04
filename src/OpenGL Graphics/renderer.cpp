//
// Created by nami on 5/14/22.
//

#include "renderer.h"
#include "../Logs/logger.h"
#include "res_loader.h"

static bool glfw_init = false;  // Flag to check glfw prepare_mesh status.

void Opengl_renderer::gl_clear_errors()
{
  while (glGetError());  // Clear all previous openGL errors before polling the next one.
}

void Opengl_renderer::reset_bg()
{
  // Clear and change the back buffer color bit with our color.
  gl_call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Opengl_renderer::set_clear_color(const Color &color)
{
  gl_call(glClearColor(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha()));
}

void Opengl_renderer::set_textures(bool enabled)
{
  if (enabled) glEnable(GL_TEXTURE_2D);
  else glDisable(GL_TEXTURE_2D);
}

void Opengl_renderer::init_graphics()
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

  gl_call(glEnable(GL_BLEND));
  gl_call(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

  //TODO: Depth clamp for later.

  // Let OpenGL do the exponential gamma correction for us so textures and colors don't appear as dark.
  gl_call(glEnable(GL_FRAMEBUFFER_SRGB));
}

const char *Opengl_renderer::get_GL_version()
{
  return (const char *) (glGetString(GL_VERSION));
}

void Opengl_renderer::show_gl_info()
{
  alert(INFO, "FETCHING OPENGL AND GLFW INFO");
  // Get openGL and GLFW version.
  int num_ext;
  gl_call(glGetIntegerv(GL_NUM_EXTENSIONS, &num_ext));
  alert(INFO, "Extensions available : %d", num_ext);
  alert(INFO, "Opengl version : %s", get_GL_version());
  alert(INFO, "GLFW Version : %s", glfwGetVersionString());
}

void Opengl_renderer::setup_mesh(const Buffer_layout &layout, const std::vector<Vertex> &vertices,
                                 const std::vector<unsigned int> &indices)
{
  this->vbo = Vertex_buffer(vertices.data(), VERTEX_SIZE * vertices.size());
  this->vao.bind();
  this->ibo = Index_buffer(indices.data(), indices.size());
  this->tex = Texture(load_texture_file("../Resources/Textures/tiles.png"));
  this->vao.add_buffer(this->vbo, layout);

  this->tex.unbind();
  this->vao.unbind();
  this->vbo.unbind();
  this->ibo.unbind();
}

void Opengl_renderer::draw() const
{
  this->vao.bind();
  this->tex.bind(0);

  // Draw from vertex_source arrays.
  gl_call(glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_INT, nullptr));
}

void Opengl_renderer::delete_buffers() const
{
  alert(INFO, "DELETING VBO...");
  this->vbo.delete_buffer();
  alert(INFO, "DELETING VAO...");
  this->vao.delete_array_buffer();
  alert(INFO, "DELETING IBO...");
  this->ibo.delete_buffer();
  alert(INFO, "DELETING TEXTURE...");
  this->tex.delete_texture();
}

void Opengl_renderer::glfw_error_callback(int error_code, const char *err_str)
{
  alert(ERROR, "[GLFW ERROR] : %s", err_str);
  if (glfw_init) glfwTerminate();  // If glfw has been initialized.
  exit(error_code);
}

void Opengl_renderer::gl_error_callback(GLenum source, const char *function_name,
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
