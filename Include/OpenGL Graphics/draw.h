//
// Created by nami on 5/7/22.
//

#ifndef OPENGL_DEV_DRAW_H
#define OPENGL_DEV_DRAW_H

#include "vertex.h"
#include "vao.h"
#include "../window.h"
#include "program.h"

typedef struct gl_data_s
{
  const char *vertex_source = nullptr;
  const char *fragment_source = nullptr;
  std::vector<Vertex> vertices;
} gl_vertex_data_s;

class Draw
{
public:
  Draw(const Window &gl_window, const Program &program, const Vao &vao);

  void init(gl_vertex_data_s);

  [[maybe_unused]] void draw_vertices(double x_pos, double y_pos, double z_pos, double alpha, float scale);

  [[maybe_unused]] void draw_color(const Color &color, float scale);

  [[maybe_unused]] void draw_colored_vertices(gl_vertex_data_s &, const Color &color, float scale);

  ~Draw();

private:
  Vao vao;
  Program current_program;
  Window gl_window;
};

#endif //OPENGL_DEV_DRAW_H
