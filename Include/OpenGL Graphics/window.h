//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_WINDOW_H
#define GAME_OPENGL_WINDOW_H

#include "render.h"
#include "shader.h"
#include "../Logs/logger.h"

class Window
{
public:
  static void setup_monitor();;
  static void create_window();
  static void clear_bg();
  static void refresh();
  [[maybe_unused]] static void hide();

  static GLFWwindow *get_window();
  [[maybe_unused]] static int get_width();
  [[maybe_unused]] static int get_height();
  [[maybe_unused]] static int get_refresh_rate();
  [[maybe_unused]] static int get_x_pos();
  [[maybe_unused]] static int get_y_pos();
  [[maybe_unused]] static float get_x_scale();
  [[maybe_unused]] static float get_y_scale();
  [[maybe_unused]] static Color get_bg_color();

  [[maybe_unused]] static void set_width(int width);
  [[maybe_unused]] static void set_height(int height);
  [[maybe_unused]] static void set_fullscreen(bool fullscreen_state);
  [[maybe_unused]] static void set_refresh_rate(int refresh_rate);

  [[maybe_unused]] static bool is_fullscreen();
  static bool is_closed();
  static void cleanup();
  [[maybe_unused]] static void set_callbacks();
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

void toggle_fullscreen(GLFWwindow *window);

void window_viewport_callback([[maybe_unused]] GLFWwindow *, int, int);

void cursor_position_callback(GLFWwindow *window, double, double);

void cursor_enter_callback([[maybe_unused]] GLFWwindow *, int);

void mouse_button_callback([[maybe_unused]] GLFWwindow *, int, int, int);

void scroll_callback([[maybe_unused]] GLFWwindow *, double, double);

void key_callback([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scan_code,
                  int action, int combination);

#endif //GAME_OPENGL_WINDOW_H
