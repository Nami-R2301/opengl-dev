//
// Created by nami on 5/13/22.
//

#ifndef OPENGL_DEV_VECTOR_3F_H
#define OPENGL_DEV_VECTOR_3F_H

#include <cmath>

class Vector_3f
{
public:
  explicit Vector_3f(float x = 0, float y = 0, float z = 0);
  [[nodiscard]] float get_x() const;
  [[nodiscard]] float get_y() const;
  [[nodiscard]] float get_z() const;
  void setX(float x);
  void setY(float y);
  void setZ(float z_);
  [[nodiscard]] float length() const;
  [[nodiscard]] float dot(const Vector_3f &other_vector) const;
  Vector_3f normalize();
  Vector_3f cross(const Vector_3f &other_vector) const;
  [[nodiscard]] Vector_3f rotate(float angle) const;
  Vector_3f operator+(const Vector_3f &other_vector) const;
  Vector_3f operator+(float coord) const;
  Vector_3f operator-(const Vector_3f &other_vector) const;
  Vector_3f operator-(float coord) const;
  Vector_3f operator*(const Vector_3f &other_vector) const;
  Vector_3f operator*(float coord) const;
  Vector_3f operator/(const Vector_3f &other_vector) const;
  Vector_3f operator/(float coord) const;
private:
  float x;
  float y;
  float z;
};

#endif //OPENGL_DEV_VECTOR_3F_H
