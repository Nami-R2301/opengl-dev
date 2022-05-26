//
// Created by nami on 5/25/22.
//

#include "../../Include/Math/camera.h"

const Vector_3f Camera::y_axis = Vector_3f(0, 1, 0);  /* NOLINT */

Camera::Camera()
{
  *this = Camera(Vector_3f(0, 0, 0), Vector_3f(0, 0, 1),
                 Vector_3f(0, 1, 0));
}

Camera::Camera(const Vector_3f &position_, const Vector_3f &forward_, const Vector_3f &up_)
{
  this->position = position_;
  this->forward = forward_;
  this->up = up_;

  // Normalize vectors.
  forward.normalize();
  up.normalize();
}

const Vector_3f &Camera::get_position() const
{
  return position;
}

__attribute__((unused)) void Camera::set_position(const Vector_3f &position_)
{
  Camera::position = position_;
}

const Vector_3f &Camera::get_forward() const
{
  return forward;
}

void Camera::set_forward(const Vector_3f &forward_)
{
  forward = forward_;
}

const Vector_3f &Camera::get_up() const
{
  return up;
}

void Camera::set_up(const Vector_3f &up_)
{
  up = up_;
}

// Gets the normalized vector facing left based on camera's forward and up vectors.
Vector_3f Camera::get_left()
{
  Vector_3f left = forward.cross(up);
  left.normalize();
  return left;
}

Vector_3f Camera::get_right()
{
  Vector_3f right = up.cross(forward);
  right.normalize();
  return right;
}

void Camera::move(const Vector_3f &direction, const float amount)
{
  this->position = this->position + (direction * amount);
}

void Camera::rotate_x(float angle)
{
  Vector_3f horizontal_axis = Camera::y_axis.cross(this->forward);
  horizontal_axis.normalize();

  this->forward = this->forward.rotate(angle, horizontal_axis);
  set_forward(this->forward.normalize());

  this->up = this->forward.cross(horizontal_axis);
  set_up(this->up.normalize());
}

void Camera::rotate_y(float angle)
{
  Vector_3f horizontal_axis = Camera::y_axis.cross(this->forward);
  horizontal_axis.normalize();

  this->forward = this->forward.rotate(angle, y_axis);
  set_forward(this->forward.normalize());

  this->up = this->forward.cross(horizontal_axis);
  set_up(this->up.normalize());
}

__attribute__((unused)) void Camera::input()
{
}
