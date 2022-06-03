//
// Created by nami on 5/14/22.
//

#pragma once

#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <vector>

#include "vertex.h"
#include "texture.h"
#include "index_buffer.h"
#include "vertex_array_buffer.h"


// Macro to log openGL errors in an efficient and clean way.
#define gl_call(x) Opengl_renderer::gl_clear_errors(); x; Opengl_renderer::gl_error_callback(glGetError(), #x, __FILE__, __LINE__)

class Opengl_renderer
{
public:
  // Initial setup.
  static void init_graphics();
  static const char *get_GL_version();
  static void set_textures(bool enabled);
  static void show_gl_info();
  void setup_mesh(const Buffer_layout &layout, const std::vector<Vertex> &vertices,
                  const std::vector<unsigned int> &indices);

  // Frame changes.
  static void reset_bg();
  void draw() const;
  static void set_clear_color(const Color &color);

  // Error handling.
  static void gl_clear_errors();
  static void glfw_error_callback(int error_code, const char *err_str);
  static void gl_error_callback(GLenum source, const char *function_name,
                                const char *source_file, unsigned int line_number);

  // Cleanup.
  void delete_buffers() const;

//  // Getters.
//  [[nodiscard]] inline const Vertex_buffer& get_vbo() const { return this->vbo; };
//  [[nodiscard]] inline const Vertex_array_buffer& get_vao() const { return this->vao; };
//  [[nodiscard]] inline const Index_buffer& get_ibo() const { return this->ibo; };
//  [[nodiscard]] inline const Texture& get_texture() const { return this->tex; };
private:
  Vertex_buffer vbo;
  Vertex_array_buffer vao;
  Index_buffer ibo;
  Texture tex;
};

