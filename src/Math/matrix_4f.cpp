//
// Created by nami on 5/14/22.
//

#include "../../Include/Math/matrix_4f.h"

Matrix_4f::Matrix_4f()
{
  this->num_rows = 4;
  this->num_cols = 4;
  for (int i = 0; i < this->num_rows; i++)
    // Initialize each cell
    for (int j = 0; j < get_num_cols(); ++j) set_value(i, j, 0);
}

Matrix_4f::Matrix_4f(const Matrix_4f &other_matrix)
{
  this->num_rows = other_matrix.get_num_rows();
  this->num_cols = other_matrix.get_num_cols();
  for (int i = 0; i < this->num_rows; i++)
    for (int j = 0; j < this->num_cols; j++)
      set_value(i, j, other_matrix.get_value(i, j));
}

glm::mat4x4 Matrix_4f::get_matrix() const
{
  return this->matrix;
}

float Matrix_4f::get_value(int row, int col) const
{
  return this->matrix[row][col];
}

void Matrix_4f::set_value(int row, int col, float value)
{
  this->matrix[row][col] = value;
}

int Matrix_4f::get_num_rows() const
{
  return num_rows;
}

int Matrix_4f::get_num_cols() const
{
  return num_cols;
}

void Matrix_4f::print_values() const
{
  for (int i = 0; i < get_num_rows(); ++i)
  {
    printf("\n");
    for (int j = 0; j < get_num_cols(); ++j)
    {
      // Last column to print.
      if ((i + 1) * (j + 1) == length()) printf("%.2f", get_value(i, j));
      else printf("%.2f, ", get_value(i, j));
    }
  }
  printf("\n");
}

Matrix_4f Matrix_4f::operator*(const Matrix_4f &other_matrix)
{
  Matrix_4f result;

  for (int i = 0; i < other_matrix.get_num_rows(); i++)
    for (int j = 0; j < other_matrix.get_num_cols(); j++)
      result.set_value(i, j, this->matrix[i][0] * other_matrix.get_value(0, j) +
                             this->matrix[i][1] * other_matrix.get_value(1, j) +
                             this->matrix[i][2] * other_matrix.get_value(2, j) +
                             this->matrix[i][3] * other_matrix.get_value(3, j)
      );
  return result;
}

int Matrix_4f::length() const
{
  return num_rows * num_cols;
}

void Matrix_4f::init_identity()
{
  for (int i = 0; i < num_rows; ++i) set_value(i, i, 1);
}

void Matrix_4f::init_translation(float x, float y, float z)
{
  init_identity();
  for (int i = 0; i < num_rows; ++i)
  {
    if (i == 0) set_value(i, get_num_cols() - 1, x);  // add x to last col (w) component.
    if (i == 1) set_value(i, get_num_cols() - 1, y);  // add y to last col (w) component.
    if (i == 2) set_value(i, get_num_cols() - 1, z);  // add z to last col (w) component.
  }
}

void Matrix_4f::init_translation(const Vector_3f &vector_3f)
{
  init_identity();
  for (int i = 0; i < num_rows; ++i)
  {
    if (i == 0) set_value(i, get_num_cols() - 1, vector_3f.get_x());  // add x to last col (w) component.
    if (i == 1) set_value(i, get_num_cols() - 1, vector_3f.get_y());  // add y to last col (w) component.
    if (i == 2) set_value(i, get_num_cols() - 1, vector_3f.get_z());  // add z to last col (w) component.
  }
}


