//
// Created by nami on 5/25/22.
//

#ifndef OPENGL_DEV_CAMERA_H
#define OPENGL_DEV_CAMERA_H

#include "vector_2f.h"
#include "vector_3f.h"
#include "../Game logic/game_time.h"
#include "../Game logic/input.h"
#include "../OpenGL Graphics/window.h"

class Camera
{
public:
  Camera();
  Camera(const Vector_3f &camera_position, const Vector_3f &camera_forward, const Vector_3f &camera_up);

  const Vector_3f &get_position() const;
  __attribute__((unused)) void set_position(const Vector_3f &position);
  const Vector_3f &get_forward() const;
  __attribute__((unused)) void set_forward(const Vector_3f &forward);
  const Vector_3f &get_up() const;
  __attribute__((unused)) void set_up(const Vector_3f &up);

  void input();
  void move(const Vector_3f &direction, float amount);
  [[nodiscard]] Vector_3f get_left();
  [[nodiscard]] Vector_3f get_right();
  void rotate_x(float angle);
  void rotate_y(float angle);
private:
  static const Vector_3f y_axis;
  static bool mouse_locked;
  static Vector_2f center_position;
  Vector_3f position;
  Vector_3f forward;
  Vector_3f up;
  Game_time time;
};

#endif //OPENGL_DEV_CAMERA_H
