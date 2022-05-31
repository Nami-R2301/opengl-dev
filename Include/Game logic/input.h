//
// Created by nami on 5/17/22.
//

#ifndef OPENGL_DEV_INPUT_H
#define OPENGL_DEV_INPUT_H

#include "../OpenGL Graphics/window.h"
#include "../Math/vector_2f.h"

#define NUM_KEY_CODES GLFW_KEY_LAST;
#define NUM_MOUSE_BUTTONS GLFW_MOUSE_BUTTON_LAST;

class Input
{
public:
  Input();

  [[nodiscard]] static bool get_key(int key_code);
  [[nodiscard]] static bool get_key_down(int key_code);
  [[nodiscard]] static bool get_key_up(int key_code);
  [[nodiscard]] static bool get_mouse(int mouse_button);
  [[nodiscard]] static bool get_mouse_down(int mouse_button);
  [[nodiscard]] static bool get_mouse_up(int mouse_button);
  [[nodiscard]] static Vector_2f get_mouse_position();

  static void set_key(int key_code, bool state);
  static void set_mouse(int mouse_button, bool state);
  static void set_cursor(int enabled);
  static void set_mouse_position(const Vector_2f &position);

  static void reset();
private:
  static const int max_num_keys = NUM_KEY_CODES;
  static const int max_mouse_buttons = NUM_MOUSE_BUTTONS;
  static bool last_keys[max_num_keys];
  static bool last_mouse[max_mouse_buttons];
};

#endif //OPENGL_DEV_INPUT_H
