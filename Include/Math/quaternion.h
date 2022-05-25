//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_QUATERNION_H
#define OPENGL_DEV_QUATERNION_H

#include <cmath>
#include "../Math/vector_3f.h"

// 4D- Vectors with the imaginary component.
class Quaternion
{
public:
  Quaternion(float x, float y, float z, float w);

  [[nodiscard]] float get_x() const;
  void set_x(float x);
  [[nodiscard]] float get_y() const;
  void set_y(float y);
  [[nodiscard]] float get_z() const;
  void set_z(float z);
  [[nodiscard]] float get_w() const;
  void set_w(float w);

  [[nodiscard]] float length() const;
  Quaternion normalize();
  [[nodiscard]] Quaternion conjugate() const;
  Quaternion multiply(Vector_3f vector_3f) const;

  Quaternion operator*(const Quaternion &other_quaternion) const;
private:
  float x;
  float y;
  float z;
  float w;
};

#endif //OPENGL_DEV_QUATERNION_H
