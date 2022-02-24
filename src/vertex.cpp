//
// Created by nami on 2022-02-23.
//

#include "../Include/vertex.h"

Vertex::Vertex(float x_coord, float y_coord, float z_coord, const Color& rgb_value)
{
  x_pos = x_coord;
  y_pos = y_coord;
  z_pos = z_coord;
  this->red = rgb_value.get_red();
  this->green = rgb_value.get_green();
  this->blue = rgb_value.get_blue();
  this->alpha = rgb_value.get_alpha();
}

Vertex::Vertex(const Vertex& _vertex_)
{
  x_pos = _vertex_.x_pos;
  y_pos = _vertex_.y_pos;
  z_pos = _vertex_.z_pos;
}

bool Vertex::operator==(const Vertex& _vertex_)
{
  if(this == &_vertex_) return true;
  return (x_pos == _vertex_.x_pos && y_pos == _vertex_.y_pos && z_pos == _vertex_.z_pos);
}

Vertex& Vertex::operator=(const Vertex& _vertex_)
{
  if(this == &_vertex_) return *this;
  x_pos = _vertex_.x_pos;
  y_pos = _vertex_.y_pos;
  z_pos = _vertex_.z_pos;
  return *this;
}

Vertex::Vertex(float x_coord, float y_coord, float z_coord, float _red_, float _green_,
               float _blue_, float _alpha_)
{
  x_pos = x_coord;
  y_pos = y_coord;
  z_pos = z_coord;
  red = _red_;
  green = _green_;
  blue = _blue_;
  alpha = _alpha_;
}
