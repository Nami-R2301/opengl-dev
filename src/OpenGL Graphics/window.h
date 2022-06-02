//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_WINDOW_H
#define GAME_OPENGL_WINDOW_H

#include <GLFW/glfw3.h>
#include "color.h"

class Window
{
public:
  static void setup_monitor();;
  static void create_window();
  static void refresh();
  static void input();
  static void toggle_fullscreen();
  static void clear_bg();
  static bool is_closed();
  static void cleanup();
  [[maybe_unused]] static void hide();

  static GLFWwindow *get_window();
  static bool is_fullscreen();
  static int get_width();
  static int get_height();
  static int get_refresh_rate();
  static int get_x_pos();
  static int get_y_pos();

  static void set_width(int width);
  static void set_height(int height);
  static void set_fullscreen(bool fullscreen_state);

  [[maybe_unused]] static float get_x_scale();
  [[maybe_unused]] static float get_y_scale();
  [[maybe_unused]] static Color get_bg_color();
  [[maybe_unused]] static void set_refresh_rate(int refresh_rate);
private:
  static GLFWwindow *window;
  static GLFWmonitor *monitor;
  static int width;
  static int height;
  static int refresh_rate;
  static int x_pos;
  static int y_pos;
  static float x_scale;
  static float y_scale;
  static Color bg_color;
  static bool fullscreen;

  static void init();
};

#endif //GAME_OPENGL_WINDOW_H
