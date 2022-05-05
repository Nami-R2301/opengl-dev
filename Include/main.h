//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_MAIN_H
#define OPENGL_DEV_MAIN_H

#include "../Include/window.h"
#include "../Include/program.h"
#include "../Include/vao.h"
#include "../Include/vbo.h"
#include "../Include/evo.h"
#include "../Include/constants.h"
#include <cmath>
#include <array>

GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle.
        5, 4, 1, // Lower right triangle.
        3, 2, 4 // Upper triangle.
    };

//typedef struct gl_object_drawn_s {
//    GLuint vertex_shader = 0;
//    GLuint fragment_shader = 0;
//    GLuint vertex_array_obj = 0;
//    GLuint vertex_buffer_obj = 0;
//    GLuint shader_program = 0;
//} gl_object_drawn_t;

typedef struct gl_data_s {
  const char *vertex_source = nullptr;
  const char *fragment_source = nullptr;
  std::array<Vertex, 6> vertices;
} gl_data_t;

void process_input(GLFWwindow *);

gl_data_t compute_data(const char *, const char *);

void debug(Vertex *data);

//gl_object_drawn_t draw(Vertex vertices[]);

#endif //OPENGL_DEV_MAIN_H

