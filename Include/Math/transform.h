//
// Created by nami on 5/19/22.
//

#ifndef OPENGL_DEV_TRANSFORM_H
#define OPENGL_DEV_TRANSFORM_H

#include "vector_3f.h"
#include "matrix_4f.h"
#include "camera.h"

class Transform
{
public:
  Transform();

  [[nodiscard]] Matrix_4f get_transformation() const;
  void set_translation(const Vector_3f &translation);
  void set_rotation(const Vector_3f &rotation_);
  void set_projection(float fov, float width, float height, float z_near, float z_far);
  Matrix_4f get_projected_transformation(const Camera &camera) const;

  [[maybe_unused]] [[nodiscard]] const Vector_3f &get_translation() const;
  [[maybe_unused]] void set_translation(float x, float y, float z);
  [[maybe_unused]] [[nodiscard]] const Vector_3f &get_rotation() const;
  [[maybe_unused]] void set_rotation(float x, float y, float z);
  [[maybe_unused]] const Vector_3f &get_scale() const;
  [[maybe_unused]] void set_scale(const Vector_3f &scale_);
private:
  Vector_3f translation;
  Vector_3f rotation;
  Vector_3f scale;
  float z_near = 0.0f;
  float z_far = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  float fov = 0.0f;
};

#endif //OPENGL_DEV_TRANSFORM_H
