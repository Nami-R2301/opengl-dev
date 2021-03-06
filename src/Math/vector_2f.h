//
// Created by nami on 5/13/22.
//

#ifndef OPENGL_DEV_VECTOR_2F_H
#define OPENGL_DEV_VECTOR_2F_H

#include <cmath>

#define VECTOR2F_SIZE sizeof(float) * 2

class Vector_2f
{
public:
  explicit Vector_2f(float x = 0, float y = 0);

  [[nodiscard]] float get_x() const;
  [[nodiscard]] float get_y() const;

  void set_x(float x);
  void set_y(float y);

  [[nodiscard]] float length() const;
  [[nodiscard]] float dot(const Vector_2f &vector_) const;
  [[nodiscard]] Vector_2f normalize() const;
  [[nodiscard]] Vector_2f absolute() const;
  [[nodiscard]] Vector_2f rotate(float angle) const;

  Vector_2f operator+(const Vector_2f &other_vector) const;
  Vector_2f operator+(float coord) const;
  Vector_2f operator-(const Vector_2f &other_vector) const;
  Vector_2f operator-(float coord) const;
  Vector_2f operator*(const Vector_2f &other_vector) const;
  Vector_2f operator*(float coord) const;
  Vector_2f operator/(const Vector_2f &other_vector) const;
  Vector_2f operator/(float coord) const;
private:
  float x;
  float y;
};

#endif //OPENGL_DEV_VECTOR_2F_H
