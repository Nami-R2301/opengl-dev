//
// Created by nami on 5/19/22.
//

#include "../../Include/Math/transform.h"

Transform::Transform()
{
  this->translation = Vector_3f(0, 0, 0);
  this->rotation = Vector_3f(0, 0, 0);
  this->scale = Vector_3f(1, 1, 1);
}

Matrix_4f Transform::get_transformation() const
{
  Matrix_4f translation_matrix, rotation_matrix, scale_matrix;

  translation_matrix.init_translation(this->translation);
  rotation_matrix.init_rotation(this->rotation);
  scale_matrix.init_scale(this->scale);

  return (translation_matrix * (rotation_matrix * scale_matrix));
}

[[maybe_unused]] const Vector_3f &Transform::get_translation() const
{
  return this->translation;
}

[[maybe_unused]] void Transform::set_translation(float x, float y, float z)
{
  this->translation = Vector_3f(x, y, z);
}

void Transform::set_translation(const Vector_3f &translation_)
{
  this->translation = translation_;
}

[[maybe_unused]] const Vector_3f &Transform::get_rotation() const
{
  return this->rotation;
}

[[maybe_unused]] void Transform::set_rotation(float x, float y, float z)
{
  this->rotation = Vector_3f(x, y, z);
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
