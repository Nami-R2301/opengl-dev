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
  init_identity();
}

Matrix_4f::Matrix_4f(const Matrix_4f &other_matrix)
{
  this->num_rows = other_matrix.get_num_rows();
  this->num_cols = other_matrix.get_num_cols();
  for (int i = 0; i < this->num_rows; i++)
    for (int j = 0; j < this->num_cols; j++)
      set_value(i, j, other_matrix.get_value(i, j));
  init_identity();
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

[[maybe_unused]] void Matrix_4f::init_translation(float x, float y, float z)
{
  for (int i = 0; i < num_rows; ++i)
  {
    if (i == 0) set_value(i, get_num_cols() - 1, x);
    if (i == 1) set_value(i, get_num_cols() - 1, y);
    if (i == 2) set_value(i, get_num_cols() - 1, z);
  }
}

void Matrix_4f::init_translation(const Vector_3f &vector_3f)
{
  for (int i = 0; i < num_rows; ++i)
  {
    if (i == 0) set_value(i, get_num_cols() - 1, vector_3f.get_x());
    if (i == 1) set_value(i, get_num_cols() - 1, vector_3f.get_y());
    if (i == 2) set_value(i, get_num_cols() - 1, vector_3f.get_z());
  }
}

void Matrix_4f::init_rotation(Vector_3f vector_3f)
{
  Matrix_4f rotation_x, rotation_y, rotation_z; // Init rotation matrices.

  // Get angles and convert to radiant.
  vector_3f.set_x((float) (vector_3f.get_x() * (M_PI / 180)));
  vector_3f.set_y((float) (vector_3f.get_y() * (M_PI / 180)));
  vector_3f.set_z((float) (vector_3f.get_z() * (M_PI / 180)));

  // Set angles for rotation matrix z.
  rotation_z.set_value(0, 0, cosf(vector_3f.get_z()));
  rotation_z.set_value(0, 1, -(sinf(vector_3f.get_z())));
  rotation_z.set_value(1, 0, sinf(vector_3f.get_z()));
  rotation_z.set_value(1, 1, cosf(vector_3f.get_z()));

  // Set angles for rotation matrix x.
  rotation_x.set_value(1, 1, cosf(vector_3f.get_x()));
  rotation_x.set_value(1, 2, -(sinf(vector_3f.get_x())));
  rotation_x.set_value(2, 1, sinf(vector_3f.get_x()));
  rotation_x.set_value(2, 2, cosf(vector_3f.get_x()));

  // Set angles for rotation matrix y.
  rotation_y.set_value(0, 0, cosf(vector_3f.get_y()));
  rotation_y.set_value(0, 2, -(sinf(vector_3f.get_y())));
  rotation_y.set_value(2, 0, sinf(vector_3f.get_y()));
  rotation_y.set_value(2, 2, cosf(vector_3f.get_y()));

  this->matrix = (rotation_z * (rotation_y * rotation_x)).get_matrix();  // Init current matrix instance.
}

void Matrix_4f::init_scale(Vector_3f vector_3f)
{
  // For every row except w.
  set_value(0, 0, vector_3f.get_x());
  set_value(1, 1, vector_3f.get_y());
  set_value(2, 2, vector_3f.get_z());
}

void Matrix_4f::init_projection(float fov_, float width_, float height_, float z_near_, float z_far_)
{
  float aspect_ratio = width_ / height_;
  auto fov_to_rad = (float) (fov_ * (M_PI / 180) / 2);
  float tan_half_fov = tanf(fov_to_rad);
  float z_range = z_near_ - z_far_;

  set_value(0, 0, 1.0f / (tan_half_fov * aspect_ratio));
  set_value(1, 1, 1.0f / tan_half_fov);
  set_value(2, 2, (-z_near_ - z_far_) / z_range);  // Scaling the z index to the range.
  set_value(2, 3, 2 * z_far_ * z_near_ / z_range);  // Scaling the z index to the range.
  set_value(3, 2, get_value(2, 2));  // Copy whatever z value we have.
  set_value(3, 3, 0.0f);  // Get rid of w.
}

void Matrix_4f::init_camera(Vector_3f forward, Vector_3f up)
{
  Vector_3f f = forward;
  f.normalize();

  Vector_3f r = up;
  r.normalize();
  r = r.cross(f);

  Vector_3f u = f.cross(r);

  matrix[0][0] = r.get_x();
  matrix[0][1] = r.get_y();
  matrix[0][2] = r.get_z();
  matrix[0][3] = 0;
  matrix[1][0] = u.get_x();
  matrix[1][1] = u.get_y();
  matrix[1][2] = u.get_z();
  matrix[1][3] = 0;
  matrix[2][0] = f.get_x();
  matrix[2][1] = f.get_y();
  matrix[2][2] = f.get_z();
  matrix[2][3] = 0;
  matrix[3][0] = 0;
  matrix[3][1] = 0;
  matrix[3][2] = 0;
  matrix[3][3] = 1;

}


