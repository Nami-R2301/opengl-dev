//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_WINDOW_H
#define GAME_OPENGL_WINDOW_H

#include "OpenGL Graphics/color.h"
#include "OpenGL Graphics/render.h"
#include <iostream>

class Window
{
public:
  Window();
  ~Window();
  Window &operator=(const Window &);
  void init();
  void show();
  [[maybe_unused]] [[nodiscard]] int get_width() const;
  [[maybe_unused]] [[nodiscard]] int get_height() const;
  [[maybe_unused]] [[maybe_unused]] [[nodiscard]] int get_refresh_rate() const;
  [[maybe_unused]] [[nodiscard]] bool is_fullscreen() const;
  [[maybe_unused]] void set_width(int width);
  [[maybe_unused]] void set_height(int height);
  [[maybe_unused]] void set_fullscreen(bool fullscreen_state);
  [[maybe_unused]] [[maybe_unused]] void set_refresh_rate(int refresh_rate);
  [[nodiscard]] GLFWwindow *get_window() const;
  [[nodiscard]] bool is_closed() const;
  void process_input();
  static void update_color(Color &);

private:
  GLFWwindow *window;
  GLFWmonitor *monitor;
  int width;
  int height;
  int refresh_rate;
  bool fullscreen;
};

void toggle_fullscreen(GLFWwindow *window);

void window_viewport_callback([[maybe_unused]] GLFWwindow *, int, int);

void cursor_position_callback(GLFWwindow *window, double, double);

void cursor_enter_callback([[maybe_unused]] GLFWwindow *, int);

void mouse_button_callback([[maybe_unused]] GLFWwindow *, int, int, int);

void scroll_callback([[maybe_unused]] GLFWwindow *, double, double);

void key_callback([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scan_code,
                  int action, int combination);

#endif //GAME_OPENGL_WINDOW_H
