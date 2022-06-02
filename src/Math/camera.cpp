//
// Created by nami on 5/25/22.
//

#include "camera.h"
#include "../Game logic/input.h"
#include "../OpenGL Graphics/window.h"

bool Camera::mouse_locked = false;
Vector_2f Camera::center_position((float) Window::get_width() / 2.0f, (float) Window::get_height() / 2.0f);  //NOLINT

const Vector_3f Camera::y_axis = Vector_3f(0, 1, 0);  // NOLINT

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
  set_forward(forward.normalize());
  set_up(up.normalize());
  this->time.set_previous_time(std::chrono::system_clock::now());
}

void Camera::input()
{
  float sensitivity = 0.10f;
  time.set_current_time(std::chrono::system_clock::now());
  float movAmt = ((10.0f * time.get_delta_time_f()) / NANO);
//  printf("Movement amount = %.2f", time.get_delta_time_f());
//		float rotAmt = (float)(100 * Game_time.getDelta());

  if (Input::get_key(GLFW_KEY_ESCAPE))
  {
    Input::set_cursor(GLFW_CURSOR_NORMAL);
    mouse_locked = false;
  }
  if (Input::get_mouse(GLFW_MOUSE_BUTTON_1))
  {
    Input::set_mouse_position(Camera::center_position);
    Input::set_cursor(GLFW_CURSOR_DISABLED);
    mouse_locked = true;
  }

  if (Input::get_key(GLFW_KEY_W)) move(get_forward(), movAmt);
  if (Input::get_key(GLFW_KEY_S)) move(get_forward(), -movAmt);
  if (Input::get_key(GLFW_KEY_A)) move(get_left(), movAmt);
  if (Input::get_key(GLFW_KEY_D)) move(get_right(), movAmt);

  if (mouse_locked)
  {
    Vector_2f deltaPos = Input::get_mouse_position() - Camera::center_position;

    bool rotation_y = deltaPos.get_x() != 0;
    bool rotation_x = deltaPos.get_y() != 0;

    if (rotation_y) rotate_y(deltaPos.get_x() * sensitivity);
    if (rotation_x) rotate_x(-deltaPos.get_y() * sensitivity);

    if (rotation_y || rotation_x) Input::set_mouse_position(Camera::center_position);
  }
  time.set_previous_time(time.get_current_time());
}

const Vector_3f &Camera::get_position() const
{
  return position;
}

const Vector_3f &Camera::get_forward() const
{
  return forward;
}

const Vector_3f &Camera::get_up() const
{
  return up;
}

// Gets the normalized vector facing left based on camera's forward and up vectors.
Vector_3f Camera::get_left()
{
  return forward.cross(up).normalize();
}

Vector_3f Camera::get_right()
{
  return up.cross(forward).normalize();
}

void Camera::move(const Vector_3f &direction, const float amount)
{
  this->position = this->position + (direction * amount);
}

void Camera::rotate_x(float angle)
{
  Vector_3f horizontal_axis = Camera::y_axis.cross(this->forward).normalize();
  this->forward = this->forward.rotate(angle, horizontal_axis).normalize();
  this->up = this->forward.cross(horizontal_axis).normalize();
}

void Camera::rotate_y(float angle)
{
  Vector_3f horizontal_axis = Camera::y_axis.cross(this->forward).normalize();
  this->forward = this->forward.rotate(angle, y_axis).normalize();
  this->up = this->forward.cross(horizontal_axis).normalize();
}

[[maybe_unused]] void Camera::set_position(const Vector_3f &position_)
{
  Camera::position = position_;
}

[[maybe_unused]] void Camera::set_forward(const Vector_3f &forward_)
{
  forward = forward_;
}

[[maybe_unused]] void Camera::set_up(const Vector_3f &up_)
{
  up = up_;
}
