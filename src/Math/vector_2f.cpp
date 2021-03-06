//
// Created by nami on 5/13/22.
//

#include "vector_2f.h"

#include <cmath>

Vector_2f::Vector_2f(float x, float y)
{
  this->x = x;
  this->y = y;
}

float Vector_2f::get_x() const
{
  return this->x;
}

float Vector_2f::get_y() const
{
  return this->y;
}

[[maybe_unused]] void Vector_2f::set_x(float x_)
{
  this->x = x_;
}

[[maybe_unused]] void Vector_2f::set_y(float y_)
{
  this->y = y_;
}

float Vector_2f::length() const
{
  return std::sqrt(this->x * this->x + this->y * this->y);
}

[[maybe_unused]] float Vector_2f::dot(const Vector_2f &vector_) const
{
  return (this->x * vector_.get_x()) + (this->y * vector_.get_y());
}

Vector_2f Vector_2f::normalize() const
{
  return Vector_2f(this->x / length(), this->y / length());
}

[[maybe_unused]] Vector_2f Vector_2f::absolute() const
{
  return Vector_2f(std::abs(this->x), std::abs(this->y));
}

[[maybe_unused]] Vector_2f Vector_2f::rotate(float angle) const
{
  double rad_angle = angle * (M_PI / 180);
  double cos_angle = std::cos(rad_angle);
  double sin_angle = std::sin(rad_angle);

  return Vector_2f((float) (this->x * cos_angle - this->y * sin_angle),
                   (float) (this->x * sin_angle + this->y * cos_angle));
}

// Add two vectors.
Vector_2f Vector_2f::operator+(const Vector_2f &other_vector) const
{
  return Vector_2f(this->x + other_vector.get_x(), this->y + other_vector.get_y());
}

Vector_2f Vector_2f::operator-(const Vector_2f &other_vector) const
{
  return Vector_2f(this->x - other_vector.get_x(), this->y - other_vector.get_y());
}

Vector_2f Vector_2f::operator*(const Vector_2f &other_vector) const
{
  return Vector_2f(this->x * other_vector.get_x(), this->y * other_vector.get_y());
}

Vector_2f Vector_2f::operator/(const Vector_2f &other_vector) const
{
  return Vector_2f(this->x / other_vector.get_x(), this->y / other_vector.get_y());
}

Vector_2f Vector_2f::operator+(float coord) const
{
  return Vector_2f(this->x + coord, this->y + coord);
}

Vector_2f Vector_2f::operator-(float coord) const
{
  return Vector_2f(this->x - coord, this->y - coord);
}

Vector_2f Vector_2f::operator*(float coord) const
{
  return Vector_2f(this->x * coord, this->y * coord);
}

Vector_2f Vector_2f::operator/(float coord) const
{
  return Vector_2f(this->x / coord, this->y / coord);
}





