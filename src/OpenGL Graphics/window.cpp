//
// Created by nami on 2022-02-23.
//

#include "../../Include/OpenGL Graphics/window.h"

GLFWwindow *Window::window = nullptr;
GLFWmonitor *Window::monitor = nullptr;  // Defaults to windowed mode.

// Default video attributes.
int Window::width = 800.0f;
int Window::height = 600.0f;
int Window::refresh_rate = 30.0f;
bool Window::fullscreen = false;

// Window attributes.
int Window::x_pos = 0;
int Window::y_pos = 0;
float Window::x_scale = 0.0f;
float Window::y_scale = 0.0f;

Color Window::bg_color;  // Default background color (gray) NOLINT;

void Window::init()
{
  glfwSetWindowAspectRatio(Window::window, 16, 9);
  glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Set our mouse cursor to default.

  /* Set our different callbacks for handling events. */
  // Make sure we finish events before treating the next ones.
  glfwSetInputMode(Window::window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Window::setup_monitor()
{
  int monitor_count;
  GLFWmonitor **monitors = glfwGetMonitors(&monitor_count);
  Logger::alert("DETECTING MONITOR...\n");
  char print_buffer[75];
  snprintf(print_buffer, sizeof(print_buffer), "Number of monitors detected : %d\n", monitor_count);
  Logger::alert(print_buffer);
  Window::monitor = monitors[0]; // Get main monitor specs.
  const GLFWvidmode *mode = glfwGetVideoMode(monitor); // Get video specs of monitor.
  Window::width = (int) (mode->width / 2);
  Window::height = (int) (mode->height / 2);
  Window::refresh_rate = mode->refreshRate;
  snprintf(print_buffer, sizeof(print_buffer),
           "Monitor stats : \tWidth : %dpx, height : %dpx, refresh rate : %dhz\n",
           mode->width, mode->height, mode->refreshRate);
  Logger::alert(print_buffer);
  glfwGetMonitorContentScale(monitor, &Window::x_scale, &Window::y_scale);  // Get monitor scale.

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

  // Hint at glfw our opengl version -> 3.3 -> [MAJOR].[MINOR] + that we have the core profile.
  // So that we will only use the modern functions in it.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::create_window()
{
  Logger::alert("CREATING WINDOW...\n");
  setup_monitor();
  // Generate a pointer to a window using our monitor info, so that we later hide it.
  Window::window = glfwCreateWindow(Window::width, Window::height, "Game",
                                    nullptr, nullptr);  // Windowed mode.
  init();
  Logger::alert("DONE CREATING WINDOW.\n");
  glfwMakeContextCurrent(Window::window); // Show our window.
  // Specify which coordinates to draw for our window -> from (0,0) to (monitor_width, monitor_height).
  glViewport(0, 0, Window::width, Window::height);
  glfwGetWindowPos(window, &Window::x_pos, &Window::y_pos);  // Get initial window position.
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

// Show the window created.
[[maybe_unused]] void Window::hide()
{
  glfwMakeContextCurrent(nullptr); // Hide our window.
}

void Window::refresh()
{
  if (is_closed()) return;
  glfwSwapBuffers(Window::window); // Update window buffer (refresh window).
  glfwSwapInterval(1);  // Disable/enable Vertical synchronisation (Vsync).
}

// Let the window open as long as the close flag (gathered by glfwPollEvents) is not set to true.
bool Window::is_closed()
{
  return glfwWindowShouldClose(Window::window);
}

// Return a glfwWindow instance in case there's a need to manipulate the window directly.
GLFWwindow *Window::get_window()
{
  return Window::window;
}

[[maybe_unused]] int Window::get_width()
{
  return Window::width;
}

[[maybe_unused]] int Window::get_height()
{
  return Window::height;
}

[[maybe_unused]] void Window::set_width(int width_)
{
  Window::width = width_;
}

[[maybe_unused]] void Window::set_height(int height_)
{
  Window::height = height_;
}

[[maybe_unused]] bool Window::is_fullscreen()
{
  return Window::fullscreen;
}

[[maybe_unused]] int Window::get_refresh_rate()
{
  return Window::refresh_rate;
}

[[maybe_unused]] void Window::set_refresh_rate(int refresh_rate_)
{
  Window::refresh_rate = refresh_rate_;
}

[[maybe_unused]] void Window::set_fullscreen(bool fullscreen_state)
{
  Window::fullscreen = fullscreen_state;
}

int Window::get_x_pos()
{
  return Window::x_pos;
}

int Window::get_y_pos()
{
  return Window::y_pos;
}

__attribute__((unused)) float Window::get_x_scale()
{
  return Window::x_scale;
}

__attribute__((unused)) float Window::get_y_scale()
{
  return Window::y_scale;
}

__attribute__((unused)) Color Window::get_bg_color()
{
  return Window::bg_color;
}

void Window::clear_bg()
{
  Render::set_clear_color(Color());
  Render::reset_bg();
}

void toggle_fullscreen(GLFWwindow *window)
{
  GLFWmonitor *monitor = glfwGetWindowMonitor(window);
  if (!monitor)
  {
    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window, monitor, Window::get_x_pos(), Window::get_y_pos(),
                         mode->width, mode->height, mode->refreshRate);
  } else
  {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetWindowMonitor(window, nullptr, Window::get_x_pos(), Window::get_y_pos(),
                         (int) (width / 2), (int) (height / 2),
                         GLFW_DONT_CARE);  // Set maximum refresh rate possible.
  }
}

// Free resources and close the window.
void Window::cleanup()
{
  Logger::alert("DESTROYING WINDOW...\t");
  glfwDestroyWindow(Window::window);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  Logger::alert("Done.\n", INFO, true);
}
