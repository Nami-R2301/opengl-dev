//
// Created by nami on 5/13/22.
//

#ifndef OPENGL_DEV_VECTOR_3F_H
#define OPENGL_DEV_VECTOR_3F_H

#include <cmath>

#define VECTOR3F_SIZE sizeof(float) * 3
#define VECTOR2F_SIZE sizeof(float) * 2

class Vector_3f
{
public:
  explicit Vector_3f(float x = 0, float y = 0, float z = 0);

  [[nodiscard]] float get_x() const;
  [[nodiscard]] float get_y() const;
  [[nodiscard]] float get_z() const;

  void set_x(float x);
  void set_y(float y);
  void set_z(float z_);

  [[nodiscard]] float length() const;
  [[nodiscard]] float dot(const Vector_3f &other_vector) const;
  [[nodiscard]] Vector_3f normalize() const;
  [[nodiscard]] Vector_3f cross(const Vector_3f &other_vector) const;
  [[nodiscard]] Vector_3f rotate(float angle, const Vector_3f &axis) const;
  [[nodiscard]] Vector_3f absolute() const;

  Vector_3f operator+(const Vector_3f &other_vector) const;
  Vector_3f operator+(float coord) const;
  Vector_3f operator-(const Vector_3f &other_vector) const;
  Vector_3f operator-(float coord) const;
  Vector_3f operator*(const Vector_3f &other_vector) const;
  Vector_3f operator*(float coord) const;
  Vector_3f operator/(const Vector_3f &other_vector) const;
  Vector_3f operator/(float coord) const;
  bool operator==(const Vector_3f &other_vector) const;
private:
  float x;
  float y;
  float z;
};

#endif //OPENGL_DEV_VECTOR_3F_H
