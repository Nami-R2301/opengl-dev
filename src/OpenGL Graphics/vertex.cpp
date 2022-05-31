//
// Created by nami on 2022-02-23.
//

#include "../../Include/OpenGL Graphics/vertex.h"

Vertex::Vertex() = default;

Vertex::Vertex(const Vector_2f &vector_2f, const Color &color)
{
  this->position = Vector_3f(vector_2f.get_x(), vector_2f.get_y(), 0.0f);
  this->color = color;
}

Vertex::Vertex(const Vector_3f &vector_3f, const Color &color)
{
  this->position = vector_3f;
  this->color = color;
}

Vertex::Vertex(const Vector_3f &position, const Vector_2f &tex_coord)
{
  this->position = position;
  this->texCoord = tex_coord;
}

Vertex::Vertex(const Vertex &_vertex_)
{
  this->position = _vertex_.position;
  this->color = _vertex_.color;
}

[[maybe_unused]] const Vector_3f &Vertex::get_position() const
{
  return position;
}

[[maybe_unused]] void Vertex::set_position(const Vector_3f &position_)
{
  Vertex::position = position_;
}

[[maybe_unused]] const Vector_2f &Vertex::get_texCoord() const
{
  return texCoord;
}

void Vertex::set_texCoord(const Vector_2f &texCoord_)
{
  Vertex::texCoord = texCoord_;
}

[[maybe_unused]] const Color &Vertex::get_color() const
{
  return color;
}

[[maybe_unused]] void Vertex::set_color(const Color &color_)
{
  Vertex::color = color_;
}

bool Vertex::operator==(const Vertex &_vertex_)
{
  if (this == &_vertex_) return true;
  return (this->position == _vertex_.position && this->color == _vertex_.color);
}

Vertex &Vertex::operator=(const Vertex &_vertex_)
{
  if (this == &_vertex_) return *this;
  this->position = _vertex_.position;
  this->color = _vertex_.color;
  return *this;
}

Vertex::Vertex(float x_coord, float y_coord, float z_coord, float _red_, float _green_,
               float _blue_, float _alpha_)
{
  this->position.set_x(x_coord);
  this->position.set_y(y_coord);
  this->position.set_z(z_coord);
  this->color = Color(_red_, _green_, _blue_, _alpha_);
}

void Vertex::print_vertex() const
{
  Logger::alert(INFO, "\nCoordinates :\nx = %.2f;\ny = %.2f;\nz = %.2f\n\nColor :\nRed = %.2f;\n"
                      "Green = %.2f;\nBlue =  %.2f;\nAlpha = %.2f", this->position.get_x(),
                this->position.get_y(), this->position.get_z(), this->color.get_red(),
                this->color.get_green(), this->color.get_blue(), this->color.get_alpha());
}

float Vertex::length() const
{
  return this->position.length();
}