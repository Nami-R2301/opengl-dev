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

[[maybe_unused]] const Vector_3f &Transform::get_scale() const
{
  return this->scale;
}

[[maybe_unused]] void Transform::set_scale(const Vector_3f &scale_)
{
  this->scale = scale_;
}

void Transform::set_projection(float fov_, float width_, float height_, float z_near_, float z_far_)
{
  this->width = width_;
  this->height = height_;
  this->fov = fov_;
  this->z_near = z_near_;
  this->z_far = z_far_;
}

Matrix_4f Transform::get_projected_transformation(const Camera &camera) const
{
  Matrix_4f model_matrix = get_transformation(), projection, view_camera_rotation, view_camera_translation;

  projection.init_projection(this->fov, this->width, this->height,
                             this->z_near, this->z_far);
  view_camera_rotation.init_camera(camera.get_forward(), camera.get_up());
  view_camera_translation.init_translation(-camera.get_position().get_x(),
                                           -camera.get_position().get_y(),
                                           -camera.get_position().get_z());

  return projection * (view_camera_rotation * (view_camera_translation * model_matrix));
}
