//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_MAIN_H
#define OPENGL_DEV_MAIN_H
#include "../Include/vertex.h"
#include "../Include/window.h"
#include "../Include/shader.h"
#include "../Include/program.h"
#include "../Include/vao.h"
#include "../Include/vbo.h"
#include <cmath>

typedef struct gl_object_drawn_s
{
  GLuint vertex_shader = 0;
  GLuint fragment_shader = 0;
  GLuint vertex_array_obj = 0;
  GLuint vertex_buffer_obj = 0;
  GLuint shader_program = 0;
} gl_object_drawn_t;

gl_object_drawn_t draw(Vertex vertices[]);

#endif //OPENGL_DEV_MAIN_H

