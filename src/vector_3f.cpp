//
// Created by nami on 5/13/22.
//

#include "../Include/vector_3f.h"

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

void Vector_3f::setX(float x_)
{
  this->x = x_;
}

void Vector_3f::setY(float y_)
{
  this->y = y_;
}

void Vector_3f::setZ(float z_)
{
  this->z = z_;
}

float Vector_3f::length() const
{
  return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector_3f::dot(const Vector_3f &other_vector) const
{
  return (this->x * other_vector.get_x()) +
         (this->y * other_vector.get_y()) +
         (this->z * other_vector.get_z());
}

Vector_3f Vector_3f::normalize()
{
  float length = this->length();
  this->x /= length, this->y /= length, this->z /= length;
  return *this;
}

Vector_3f Vector_3f::cross(const Vector_3f &other_vector) const
{
  float x_ = this->y * other_vector.get_z() - this->z * other_vector.get_y();
  float y_ = this->z * other_vector.get_x() - this->x * other_vector.get_z();
  float z_ = this->x * other_vector.get_y() - this->y * other_vector.get_x();
  return Vector_3f(x_, y_, z_);
}

Vector_3f Vector_3f::rotate(float angle) const
{
  return Vector_3f();
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

