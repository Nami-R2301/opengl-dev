//
// Created by nami on 5/7/22.
//

#include "../Include/draw.h"

Draw::Draw(const Window &gl_window, const Program &program, const Vao &vertex_array_obj)
{
  this->gl_window = gl_window;
  this->vao = vertex_array_obj;
  this->current_program = program;
}

[[maybe_unused]] void Draw::draw_vertices(const double x_pos, const double y_pos, const double z_pos,
                                          const double alpha, float scale)
{

}

[[maybe_unused]] void Draw::draw_color(const Color &, float scale)
{

}

[[maybe_unused]] void Draw::draw_colored_vertices(gl_vertex_data_s &data, const Color &color, float scale)
{
}

Draw::~Draw() = default;

