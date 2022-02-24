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
  [[nodiscard]] GLFWwindow* get_window() const;
  [[nodiscard]] bool is_closed() const;
  void update_color(Color&) ;

private:
  GLFWwindow* window;
  GLFWmonitor* monitor;
  const GLFWvidmode* mode;
};


#endif //GAME_OPENGL_WINDOW_H
