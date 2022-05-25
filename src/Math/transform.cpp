//
// Created by nami on 5/19/22.
//

#include "../../Include/Math/transform.h"

// Projection variables.
float Transform::z_near, Transform::z_far, Transform::width, Transform::height, Transform::fov;
Camera Transform::camera;  /* NOLINT */

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

__attribute__((unused)) const Vector_3f &Transform::get_scale() const
{
  return this->scale;
}

void Transform::set_scale(const Vector_3f &scale_)
{
  this->scale = scale_;
}

const Camera &Transform::get_camera()
{
  return camera;
}

void Transform::set_camera(const Camera &camera_)
{
  Transform::camera = camera_;
}

void Transform::set_projection(float fov_, float width_, float height_, float z_near_, float z_far_)
{
  Transform::width = width_;
  Transform::height = height_;
  Transform::fov = fov_;
  Transform::z_near = z_near_;
  Transform::z_far = z_far_;
}

Matrix_4f Transform::get_projected_transformation() const
{
  Matrix_4f transformation = get_transformation(), projection, camera_rotation, camera_translation;

  projection.init_projection(Transform::fov, Transform::width, Transform::height,
                             Transform::z_near, Transform::z_far);
  camera_rotation.init_camera(Transform::camera.get_forward(), Transform::camera.get_up());
  camera_translation.init_translation(-Transform::camera.get_position().get_x(),
                                      -Transform::camera.get_position().get_y(),
                                      -Transform::camera.get_position().get_z());

  return projection * (camera_rotation * (camera_translation * transformation));
}
