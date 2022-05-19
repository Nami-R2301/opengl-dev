//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_MATRIX4F_H
#define OPENGL_DEV_MATRIX4F_H

#include <cstdlib>
#include <cmath>
#include <cstdio>

class Matrix4f
{
public:
  explicit Matrix4f(int size = 16);
  [[maybe_unused]] Matrix4f(const Matrix4f &other_matrix);
  ~Matrix4f();
  [[nodiscard]] int length() const;
  void init_identity();
  Matrix4f operator*(const Matrix4f &other_matrix);
  [[nodiscard]] float **get_matrix() const;
  [[nodiscard]] float get_value(int row, int col) const;
  void set_value(int row, int col, float value);
  void print_values() const;
  [[nodiscard]] int get_num_rows() const;
  [[nodiscard]] int get_num_cols() const;
private:
  int num_rows;
  int num_cols;
  float **matrix;
};

#endif //OPENGL_DEV_MATRIX4F_H
