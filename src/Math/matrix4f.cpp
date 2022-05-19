//
// Created by nami on 5/14/22.
//

#include "../../Include/Math/matrix4f.h"

Matrix4f::Matrix4f(const int size)
{
  if (size < 0)
  {
    this->num_cols = 4, this->num_rows = 4;
  } else
  {
    // Equal number of rows and columns.
    this->num_cols = (int) std::sqrt(size);
    this->num_rows = (int) std::sqrt(size);
  }
  this->matrix = new float *[this->num_rows];
  for (int i = 0; i < this->num_rows; i++)
  {
    this->matrix[i] = new float[this->num_cols];
    // Initialize each cell for Valgrind.
    for (int j = 0; j < get_num_cols(); ++j) set_value(i, j, 0);
  }
}

Matrix4f::Matrix4f(const Matrix4f &other_matrix)
{
  this->num_rows = other_matrix.get_num_rows();
  this->num_cols = other_matrix.get_num_cols();
  this->matrix = new float *[this->num_rows];
  for (int i = 0; i < this->num_rows; i++)
  {
    this->matrix[i] = new float[this->num_cols];
    for (int j = 0; j < this->num_cols; j++)
    {
      set_value(i, j, other_matrix.get_value(i, j));
    }
  }
}

Matrix4f::~Matrix4f()
{
  for (int i = 0; i < get_num_cols(); i++) delete[] this->matrix[i];
  delete[] this->matrix;
}

int Matrix4f::length() const
{
  return num_rows * num_cols;
}

void Matrix4f::init_identity()
{
  for (int i = 0; i < num_rows; ++i) this->matrix[i][i] = 1;
}

const float *const Matrix4f::get_value(int row, int col) const
{
  return this->matrix[row][col];
}

void Matrix4f::set_value(int row, int col, float value)
{
  this->matrix[row][col] = value;
}

int Matrix4f::get_num_rows() const
{
  return num_rows;
}

int Matrix4f::get_num_cols() const
{
  return num_cols;
}

void Matrix4f::print_values() const
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

Matrix4f Matrix4f::operator*(const Matrix4f &other_matrix)
{
  Matrix4f result(other_matrix.length());

  for (int i = 0; i < other_matrix.get_num_rows(); i++)
  {
    for (int j = 0; j < other_matrix.get_num_cols(); j++)
    {
      result.set_value(i, j, this->matrix[i][0] * other_matrix.get_value(0, j) +
                             this->matrix[i][1] * other_matrix.get_value(1, j) +
                             this->matrix[i][2] * other_matrix.get_value(2, j) +
                             this->matrix[i][3] * other_matrix.get_value(3, j)
      );
    }
  }
  return result;
}

const float **Matrix4f::get_matrix() const
{
  return this->matrix;
}
