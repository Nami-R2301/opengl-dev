//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_MATRIX_4F_H
#define OPENGL_DEV_MATRIX_4F_H

#include <cmath>  // Cos, sin and sqrt functions.
#include <cstdio>  // Printf.
#include "vector_3f.h"  // Own 3D vector implementation.
#include <glm/glm/ext.hpp>  // Mat4x4 and value_ptr.

class Matrix_4f
{
public:
  Matrix_4f();
  [[maybe_unused]] Matrix_4f(const Matrix_4f &other_matrix);
  void init_identity();
  [[maybe_unused]] void init_translation(float x, float y, float z);
  void init_translation(const Vector_3f &vector_3f);
  void init_rotation(Vector_3f vector_3f);
  void init_scale(Vector_3f vector_3f);
  void init_projection(float fov_, float width_, float height_, float z_near_, float z_far_);
  void init_camera(Vector_3f forward, Vector_3f up);

  [[nodiscard]] int length() const;
  [[nodiscard]] glm::mat4x4 get_matrix() const;
  [[nodiscard]] float get_value(int row, int col) const;
  [[nodiscard]] int get_num_rows() const;
  [[nodiscard]] int get_num_cols() const;
  void set_value(int row, int col, float value);
  void print_values() const;

  Matrix_4f operator*(const Matrix_4f &other_matrix);
private:
  int num_rows;
  int num_cols;
  glm::mat4x4 matrix = glm::mat4x4();
};

#endif //OPENGL_DEV_MATRIX_4F_H
