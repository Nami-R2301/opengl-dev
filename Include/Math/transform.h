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
  [[maybe_unused]] [[nodiscard]] const Vector_3f &get_translation() const;
  [[maybe_unused]] void set_translation(float x, float y, float z);
  void set_translation(const Vector_3f &translation);
  [[maybe_unused]] [[nodiscard]] const Vector_3f &get_rotation() const;
  [[maybe_unused]] void set_rotation(float x, float y, float z);
  void set_rotation(const Vector_3f &rotation_);
  __attribute__((unused)) const Vector_3f &get_scale() const;
  void set_scale(const Vector_3f &scale_);
  static void set_projection(float fov, float width, float height, float z_near, float z_far);
  Matrix_4f get_projected_transformation() const;
  static const Camera &get_camera();
  static void set_camera(const Camera &camera_);
private:
  Vector_3f translation;
  Vector_3f rotation;
  Vector_3f scale;
  static Camera camera;
  static float z_near;
  static float z_far;
  static float width;
  static float height;
  static float fov;
};

#endif //OPENGL_DEV_TRANSFORM_H
