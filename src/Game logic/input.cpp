//
// Created by nami on 5/17/22.
//

#include "../../Include/Game logic/input.h"

bool Input::last_keys[max_num_keys];
bool Input::last_mouse[max_mouse_buttons];

Input::Input()
{
  glfwSetInputMode(Window::get_window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Set our mouse cursor to default.

  /* Set our different callbacks for handling events. */
  // Make sure we finish events before treating the next ones.
  glfwSetInputMode(Window::get_window(), GLFW_STICKY_KEYS, GLFW_TRUE);
  glfwSetInputMode(Window::get_window(), GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
  for (int i = 0; i < max_num_keys; i++) set_key(i, false);
  for (int i = 0; i < max_mouse_buttons; i++) set_mouse(i, false);
}

void Input::reset()
{
  for (int i = 0; i < max_num_keys; i++) set_key(i, GLFW_RELEASE);
  for (int i = 0; i < max_mouse_buttons; i++) set_mouse(i, GLFW_RELEASE);
}

bool Input::get_key(int key_code)
{
  return key_code <= max_num_keys && glfwGetKey(Window::get_window(), key_code);
}

bool Input::get_key_down(int key_code)
{
  return get_key(key_code) && !last_keys[key_code];  // When a key is not already pressed.
}

bool Input::get_key_up(int key_code)
{
  return get_key(key_code) && last_keys[key_code];  // When a mouse button is not already pressed.
}

bool Input::get_mouse(int mouse_button)
{
  return mouse_button <= max_mouse_buttons && glfwGetMouseButton(Window::get_window(), mouse_button);
}

bool Input::get_mouse_up(int mouse_button)
{
  return !get_mouse(mouse_button) && last_mouse[mouse_button];
}

bool Input::get_mouse_down(int mouse_button)
{
  return get_mouse(mouse_button) && !last_mouse[mouse_button];
}

void Input::set_key(int key_code, bool state)
{
  last_keys[key_code] = state;
}

void Input::set_mouse(int mouse_button, bool state)
{
  last_mouse[mouse_button] = state;
}

void Input::set_mouse_position(const Vector_2f &position)
{
  glfwSetCursorPos(Window::get_window(), position.get_x(), position.get_y());
}

Vector_2f Input::get_mouse_position()
{
  double position_x = 0.0f, position_y = 0.0f;
  glfwGetCursorPos(Window::get_window(), &position_x, &position_y);
  return Vector_2f((float) position_x, (float) position_y);
}

void Input::set_cursor(int enabled)
{
  glfwSetInputMode(Window::get_window(), GLFW_CURSOR, enabled);
}
