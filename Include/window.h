//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_WINDOW_H
#define GAME_OPENGL_WINDOW_H
#include <GLFW/glfw3.h>
#include "../Include/color.h"
#include <iostream>

class Window
{
public:
  Window();
  ~Window();
  void show();
  [[nodiscard]] GLFWwindow *get_window() const;

  [[nodiscard]] bool is_closed() const;

  void process_input();

  static void update_color(Color &);

private:
  GLFWwindow *window;
  GLFWmonitor *monitor;
  const GLFWvidmode *mode;
};

void window_viewport_callback([[maybe_unused]] GLFWwindow *, int, int);

void cursor_position_callback(GLFWwindow *window, double, double);

void cursor_enter_callback([[maybe_unused]] GLFWwindow *, int);

void mouse_button_callback([[maybe_unused]] GLFWwindow *, int, int, int);

void scroll_callback([[maybe_unused]] GLFWwindow *, double, double);


#endif //GAME_OPENGL_WINDOW_H
