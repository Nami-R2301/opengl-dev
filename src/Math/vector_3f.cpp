//
// Created by nami on 5/13/22.
//

#include "vector_3f.h"
#include "quaternion.h"

Vector_3f::Vector_3f(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

float Vector_3f::get_x() const
{
  return this->x;
}

float Vector_3f::get_y() const
{
  return this->y;
}

float Vector_3f::get_z() const
{
  return this->z;
}

void Vector_3f::set_x(float x_)
{
  this->x = x_;
}

void Vector_3f::set_y(float y_)
{
  this->y = y_;
}

void Vector_3f::set_z(float z_)
{
  this->z = z_;
}

float Vector_3f::length() const
{
  return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

[[maybe_unused]] float Vector_3f::dot(const Vector_3f &other_vector) const
{
  return (this->x * other_vector.get_x()) +
         (this->y * other_vector.get_y()) +
         (this->z * other_vector.get_z());
}

Vector_3f Vector_3f::normalize() const
{
  float length = this->length();
  return Vector_3f(this->x / length, this->y / length, this->z / length);
}

Vector_3f Vector_3f::cross(const Vector_3f &other_vector) const
{
  float x_ = this->y * other_vector.get_z() - this->z * other_vector.get_y();
  float y_ = this->z * other_vector.get_x() - this->x * other_vector.get_z();
  float z_ = this->x * other_vector.get_y() - this->y * other_vector.get_x();
  return Vector_3f(x_, y_, z_);
}

Vector_3f Vector_3f::rotate(float angle, const Vector_3f &axis) const
{
  auto angle_to_rad = (float) (angle * (M_PI / 180));
  float sin_half_angle = sinf(angle_to_rad / 2);
  float cos_half_angle = cosf(angle_to_rad / 2);

  float rotation_x = axis.get_x() * sin_half_angle, rotation_y = axis.get_y() * sin_half_angle,
      rotation_z = axis.get_z() * sin_half_angle, rotation_w = cos_half_angle;

  Quaternion rotation(rotation_x, rotation_y, rotation_z, rotation_w);
  Quaternion conjugate = rotation.conjugate();
  Quaternion w = (rotation.multiply(*this)) * conjugate;

  return Vector_3f(w.get_x(), w.get_y(), w.get_z());
}

[[maybe_unused]] Vector_3f Vector_3f::absolute() const
{
  return Vector_3f(std::abs(this->x), std::abs(this->y), std::abs(this->z));
}

// Add two vectors.
Vector_3f Vector_3f::operator+(const Vector_3f &other_vector) const
{
  return Vector_3f(this->x + other_vector.get_x(),
                   this->y + other_vector.get_y(),
                   this->z + other_vector.get_z());
}

Vector_3f Vector_3f::operator-(const Vector_3f &other_vector) const
{
  return Vector_3f(this->x - other_vector.get_x(),
                   this->y - other_vector.get_y(),
                   this->z - other_vector.get_z());
}

Vector_3f Vector_3f::operator*(const Vector_3f &other_vector) const
{
  return Vector_3f(this->x * other_vector.get_x(),
                   this->y * other_vector.get_y(),
                   this->z * other_vector.get_z());
}

Vector_3f Vector_3f::operator/(const Vector_3f &other_vector) const
{
  return Vector_3f(this->x / other_vector.get_x(),
                   this->y / other_vector.get_y(),
                   this->z / other_vector.get_z());
}

Vector_3f Vector_3f::operator+(float coord) const
{
  return Vector_3f(this->x + coord,
                   this->y + coord,
                   this->z + coord);
}

Vector_3f Vector_3f::operator-(float coord) const
{
  return Vector_3f(this->x - coord,
                   this->y - coord,
                   this->z - coord);
}

Vector_3f Vector_3f::operator*(float coord) const
{
  return Vector_3f(this->x * coord,
                   this->y * coord,
                   this->z * coord);
}

Vector_3f Vector_3f::operator/(float coord) const
{
  return Vector_3f(this->x / coord,
                   this->y / coord,
                   this->z / coord);
}

bool Vector_3f::operator==(const Vector_3f &other_vector) const
{
  if (this == &other_vector) return true;
  if (this->length() != other_vector.length()) return false;
  return (this->x == other_vector.get_x() &&
          this->y == other_vector.get_y() &&
          this->z == other_vector.get_z());
}

