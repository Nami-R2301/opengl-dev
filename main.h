//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_MAIN_H
#define OPENGL_DEV_MAIN_H
#include <GLES3/gl3.h>

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "uniform float size;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
                                 "}\0";
//Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 color;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = color;\n"
                                   "}\n\0";

// Vertex to pass on to our opengl vertex shaders.
typedef struct gl_vertex_s
{
  GLfloat x_pos = 0.0f;
  GLfloat y_pos = 0.0f;
  GLfloat z_pos = 0.0f;
} gl_vertex_t;

typedef struct gl_object_drawn_s
{
  GLuint vertex_shader = 0;
  GLuint fragment_shader = 0;
  GLuint vertex_array_obj = 0;
  GLuint vertex_buffer_obj = 0;
  GLuint shader_program = 0;
} gl_object_drawn_t;

gl_object_drawn_t draw(gl_vertex_t vertices[]);


#endif //OPENGL_DEV_MAIN_H

