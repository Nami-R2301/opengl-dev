//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_MATRIX_4F_H
#define OPENGL_DEV_MATRIX_4F_H

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include "vector_3f.h"
#include <glm/glm/ext.hpp>

class Matrix_4f
{
public:
  Matrix_4f();
  [[maybe_unused]] Matrix_4f(const Matrix_4f &other_matrix);
  void init_identity();
  void init_translation(float x, float y, float z);
  void init_translation(const Vector_3f &vector_3f);

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
