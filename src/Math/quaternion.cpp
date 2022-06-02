//
// Created by nami on 5/14/22.
//

#include "quaternion.h"

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
  return {-this->x, -this->y, -this->z, this->w};
}

Quaternion Quaternion::operator*(const Quaternion &r) const
{
  float w_ = w * r.get_w() - x * r.get_x() - y * r.get_y() - z * r.get_z();
  float x_ = x * r.get_w() + w * r.get_x() + y * r.get_z() - z * r.get_y();
  float y_ = y * r.get_w() + w * r.get_y() + z * r.get_x() - x * r.get_z();
  float z_ = z * r.get_w() + w * r.get_z() + x * r.get_y() - y * r.get_x();

  return {x_, y_, z_, w_};
}

Quaternion Quaternion::multiply(Vector_3f r) const
{
  float w_ = -x * r.get_x() - y * r.get_y() - z * r.get_z();
  float x_ = w * r.get_x() + y * r.get_z() - z * r.get_y();
  float y_ = w * r.get_y() + z * r.get_x() - x * r.get_z();
  float z_ = w * r.get_z() + x * r.get_y() - y * r.get_x();
  return {x_, y_, z_, w_};
}
