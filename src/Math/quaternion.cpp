//
// Created by nami on 5/14/22.
//

#include "../../Include/Math/quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

float Quaternion::get_x() const
{
  return x;
}

void Quaternion::set_x(float x_)
{
  Quaternion::x = x_;
}

float Quaternion::get_y() const
{
  return y;
}

void Quaternion::set_y(float y_)
{
  Quaternion::y = y_;
}

float Quaternion::get_z() const
{
  return z;
}

void Quaternion::set_z(float z_)
{
  Quaternion::z = z_;
}

float Quaternion::get_w() const
{
  return w;
}

void Quaternion::set_w(float w_)
{
  Quaternion::w = w_;
}

float Quaternion::length() const
{
  return std::sqrt(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::normalize()
{
  float length = this->length();
  this->x /= length, this->y /= length, this->z /= length, this->w /= length;
  return *this;
}

Quaternion Quaternion::conjugate() const
{
  return Quaternion(-this->x, -this->y, -this->z, this->w);
}

Quaternion Quaternion::operator*(const Quaternion &other_quaternion) const
{
  float w_ = w * other_quaternion.get_w() - x * other_quaternion.get_x()
             - y * other_quaternion.get_y() - z * other_quaternion.get_z();
  float x_ = x * other_quaternion.get_w() + w * other_quaternion.get_x()
             + y * other_quaternion.get_z() - z * other_quaternion.get_y();
  float y_ = y * other_quaternion.get_w() + w * other_quaternion.get_y()
             + z * other_quaternion.get_x() - x * other_quaternion.get_z();
  float z_ = z * other_quaternion.get_w() + w * other_quaternion.get_z()
             + x * other_quaternion.get_y() - y * other_quaternion.get_x();

  return Quaternion(x_, y_, z_, w_);
}

Quaternion Quaternion::operator*(const Vector_3f &vector_3f) const
{
  float w_ = -x * vector_3f.get_x() - y * vector_3f.get_y() - z * vector_3f.get_z();
  float x_ = w * vector_3f.get_x() + y * vector_3f.get_z() - z * vector_3f.get_y();
  float y_ = w * vector_3f.get_y() + z * vector_3f.get_x() - x * vector_3f.get_z();
  float z_ = w * vector_3f.get_z() + x * vector_3f.get_y() - y * vector_3f.get_x();
  return Quaternion(x_, y_, z_, w_);
}
