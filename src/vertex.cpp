//
// Created by nami on 2022-02-23.
//

#include <cstdio>
#include "../Include/vertex.h"

Vertex::Vertex(float x_coord, float y_coord, float z_coord, const Color &color)
{
  x_pos = x_coord;
  y_pos = y_coord;
  z_pos = z_coord;
  this->color = color;
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

Vertex& Vertex::operator=(const Vertex& _vertex_) {
  if (this == &_vertex_) return *this;
  this->x_pos = _vertex_.x_pos;
  this->y_pos = _vertex_.y_pos;
  this->z_pos = _vertex_.z_pos;
  this->color = _vertex_.color;
  return *this;
}

Vertex::Vertex(float x_coord, float y_coord, float z_coord, float _red_, float _green_,
               float _blue_, float _alpha_) {
  this->x_pos = x_coord;
  this->y_pos = y_coord;
  this->z_pos = z_coord;
  this->color = Color(_red_, _green_, _blue_, _alpha_);
}

void Vertex::print_vertex() const {
  printf("\nCoordinates :\nx = %.2f;\ny = %.2f;\nz = %.2f\n\nColor :\nRed = %.2f;\n"
         "Green = %.2f;\nBlue =  %.2f;\nAlpha = %.2f\n", this->x_pos, this->y_pos, this->z_pos, this->color.get_red(),
         this->color.get_green(), this->color.get_blue(), this->color.get_alpha());
}

Vertex::Vertex() = default;
