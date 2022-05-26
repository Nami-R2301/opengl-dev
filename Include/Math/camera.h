//
// Created by nami on 5/25/22.
//

#ifndef OPENGL_DEV_CAMERA_H
#define OPENGL_DEV_CAMERA_H

#include "vector_3f.h"

class Camera
{
public:
  Camera();
  Camera(const Vector_3f &camera_position, const Vector_3f &camera_forward, const Vector_3f &camera_up);

  const Vector_3f &get_position() const;
  void set_position(const Vector_3f &position);
  const Vector_3f &get_forward() const;
  void set_forward(const Vector_3f &forward);
  const Vector_3f &get_up() const;
  void set_up(const Vector_3f &up);

  void input();
  void move(const Vector_3f &direction, float amount);
  [[nodiscard]] Vector_3f get_left();
  [[nodiscard]] Vector_3f get_right();
  void rotate_x(float angle);
  void rotate_y(float angle);
private:
  static const Vector_3f y_axis;
  Vector_3f position;
  Vector_3f forward;
  Vector_3f up;
};

#endif //OPENGL_DEV_CAMERA_H
