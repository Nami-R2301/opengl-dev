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
#include "../Include/evo.h"
#include <cmath>

typedef struct gl_object_drawn_s
{
  GLuint vertex_shader = 0;
  GLuint fragment_shader = 0;
  GLuint vertex_array_obj = 0;
  GLuint vertex_buffer_obj = 0;
  GLuint shader_program = 0;
} gl_object_drawn_t;

typedef struct gl_data_s
{
  const char* vertex_source = nullptr;
  const char* fragment_source = nullptr;
  Vertex* vertices = nullptr;
} gl_data_t;

gl_data_t compute_data();
void debug(Vertex* data);
gl_object_drawn_t draw(Vertex vertices[]);

#endif //OPENGL_DEV_MAIN_H

