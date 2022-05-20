//
// Created by nami on 5/19/22.
//

#include "../../Include/Math/transform.h"

Transform::Transform()
{
  this->translation = Vector_3f(0, 0, 0);
}

Matrix_4f Transform::get_transformation() const
{
  Matrix_4f translation_matrix = Matrix_4f();
  translation_matrix.init_translation(this->translation);
  return translation_matrix;
}

const Vector_3f &Transform::get_translation() const
{
  return this->translation;
}

void Transform::set_translation(float x, float y, float z)
{
  this->translation.set_x(x);
  this->translation.set_y(y);
  this->translation.set_z(z);
}

void Transform::set_translation(const Vector_3f &translation_)
{
  this->translation = translation_;
}

const Vector_3f &Transform::get_rotation() const
{
  return rotation;
}

void Transform::set_rotation(const Vector_3f &rotation_)
{
  this->rotation = rotation_;
}

const Vector_3f &Transform::get_scale() const
{
  return this->scale;
}

void Transform::set_scale(const Vector_3f &scale_)
{
  this->scale = scale_;
}
