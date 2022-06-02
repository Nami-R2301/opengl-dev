//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_RENDERER_H
#define OPENGL_DEV_RENDERER_H

#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include "color.h"

// Macro to log openGL errors in an efficient and clean way.
#define gl_call(x) gl_clear_errors(); x; gl_error_callback(glGetError(), #x, __FILE__, __LINE__)

// Initial setup.
void init_graphics();
const char *get_GL_version();
void set_textures(bool enabled);
void show_gl_info();

void add_vbo(const unsigned int *vbo_id);
void add_vao(const unsigned int *vao_id);
void add_ibo(const unsigned int *ibo_id);

void bind_vbo(const unsigned int *vbo_id);
void bind_vao(const unsigned int *vao_id);
void bind_ibo(const unsigned int *ibo_id);
void bind_tex(const unsigned int *tex_id, unsigned int slot = 0);

void unbind_vbo();
void unbind_vao();
void unbind_ibo();
void unbind_tex();

void delete_vbo(const unsigned int *vbo);
void delete_vao(const unsigned int *vao);
void delete_ibo(const unsigned int *ibo);
void delete_tex(const unsigned int *tex);

// Frame changes.
void reset_bg();
void set_clear_color(const Color &color);

// Error handling.
void gl_clear_errors();
void glfw_error_callback(int error_code, const char *err_str);
void gl_error_callback(GLenum source, const char *function_name,
                       const char *source_file, unsigned int line_number);

#endif //OPENGL_DEV_RENDERER_H
