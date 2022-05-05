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

  static void update_color(Color &);

private:
  GLFWwindow *window;
  GLFWmonitor *monitor;
  const GLFWvidmode *mode;
};

void framebuffer_size_callback([[maybe_unused]] GLFWwindow *, int, int);


#endif //GAME_OPENGL_WINDOW_H
