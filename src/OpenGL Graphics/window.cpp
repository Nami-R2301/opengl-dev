//
// Created by nami on 2022-02-23.
//

#include "../../Include/OpenGL Graphics/window.h"

Window::Window()
{
  // Default video settings for window.
  this->monitor = nullptr;
  this->height = 600.0f;
  this->width = 800.0f;
  this->refresh_rate = 30.0;
  this->fullscreen = true;
}

void Window::init()
{
  glfwSetWindowAspectRatio(window, 16, 9);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Set our mouse cursor to default.

  /* Set our different callbacks for handling events. */
  // Make sure we finish events before treating the next ones.
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Window::setup_monitor()
{
  monitor = glfwGetPrimaryMonitor(); // Get main monitor specs.
  const GLFWvidmode *mode = glfwGetVideoMode(monitor); // Get video specs of monitor.
  width = (int) (mode->width / 2);
  height = (int) (mode->height / 2);
  refresh_rate = mode->refreshRate;
  fullscreen = false;
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

Window &Window::operator=(const Window &other_window)
{
  if (this == &other_window) return *this;
  this->window = other_window.window;
  this->monitor = other_window.monitor;
  this->width = other_window.width;
  this->height = other_window.height;
  this->refresh_rate = other_window.refresh_rate;
  this->fullscreen = other_window.fullscreen;
  return *this;
}

void Window::create_window()
{
  output_on_screen("CREATING WINDOW...\t");
  setup_monitor();
  // Generate a pointer to a window using our monitor info, so that we later hide it.
  this->window = glfwCreateWindow(this->width, this->height, "Game",
                                  nullptr, nullptr);  // Windowed mode.
  init();
  output_on_screen("Done.\n", INFO, true);
  glfwMakeContextCurrent(this->window); // Show our window.
  // Specify which coordinates to draw for our window -> from (0,0) to (monitor_width, monitor_height).
  glViewport(0, 0, this->width, this->height);
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
  glfwSwapBuffers(this->window); // Update window buffer (refresh window).
  glfwSwapInterval(1);  // Disable/enable Vertical synchronisation (Vsync).
}

// Return a glfwWindow instance in case there's a need to manipulate the window directly.
GLFWwindow *Window::get_window() const
{
  return this->window;
}

// Let the window open as long as the close flag (gathered by glfwPollEvents) is not set to true.
bool Window::is_closed() const
{
  return glfwWindowShouldClose(this->window);
}

void Window::update_color(Color &new_color)
{
  rgb_color_s new_rgb_color = new_color.get_rgb_values();
  glClearColor(new_rgb_color.red, new_rgb_color.green, new_rgb_color.blue, new_rgb_color.alpha);
  Render::reset();
}

[[maybe_unused]] void Window::update_color(float red, float green, float blue, float alpha)
{
  glClearColor(red, green, blue, alpha);
  Render::reset();
}

[[maybe_unused]] int Window::get_width() const
{
  return this->width;
}

[[maybe_unused]] int Window::get_height() const
{
  return this->height;
}

[[maybe_unused]] void Window::set_width(int width_)
{
  this->width = width_;
}

[[maybe_unused]] void Window::set_height(int height_)
{
  this->height = height_;
}

[[maybe_unused]] bool Window::is_fullscreen() const
{
  return this->fullscreen;
}

[[maybe_unused]] int Window::get_refresh_rate() const
{
  return this->refresh_rate;
}

[[maybe_unused]] void Window::set_refresh_rate(int refresh_rate_)
{
  this->refresh_rate = refresh_rate_;
}

[[maybe_unused]] void Window::set_fullscreen(bool fullscreen_state)
{
  this->fullscreen = fullscreen_state;
}

void toggle_fullscreen(GLFWwindow *window)
{
  GLFWmonitor *monitor = glfwGetWindowMonitor(window);
  if (!monitor)
  {
    monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height,
                         mode->refreshRate);
  } else
  {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glfwSetWindowMonitor(window, nullptr, (int) (width / 1.02), height / 4,
                         (int) (width / 2), (int) (height / 2),
                         GLFW_DONT_CARE);
  }
}

/******************************CALLBACKS****************************/

// Whenever the window size changed (by OS or user resize) this callback function executes
void window_viewport_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
  /* make sure the viewport matches the new window dimensions; note that width and
   * height will be significantly larger than specified on retina displays.
   */
  glViewport(0, 0, width, height);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

// Whenever the cursor changes position within the window, this callback function executes.
void cursor_position_callback([[maybe_unused]] GLFWwindow *window, double x_pos, double y_pos)
{
  int window_width = 0, window_height = 0;
  glfwGetWindowSize(window, &window_width, &window_height);
  fflush(stdout);
  if (!glfwWindowShouldClose(window) && (x_pos <= window_width && y_pos <= window_height)) {
    // For debugging purposes.
    //printf("\nX coordinate : %.2f\nY coordinate : %.2f\n", x_pos, y_pos);
  }
}

// Whenever the mouse cursor enters or leaves the window, this callback function executes.
void cursor_enter_callback([[maybe_unused]] GLFWwindow *window, int entered)
{
  fflush(stdout);
  if (!glfwWindowShouldClose(window) && entered) output_on_screen("Mouse entered\n", INFO);
  else if (!glfwWindowShouldClose(window) && !entered) output_on_screen("Mouse left\n", INFO);
}

// Whenever a mouse button is pressed or released, this callback function executes.
void mouse_button_callback([[maybe_unused]] GLFWwindow *window, int button, int action, int combination)
{
  int window_width = 0, window_height = 0;
  double cursor_x_pos = 0.0f, cursor_y_pos = 0.0f;
  glfwGetWindowSize(window, &window_width, &window_height);
  glfwGetCursorPos(window, &cursor_x_pos, &cursor_y_pos);
  //printf("\nCURSOR IS AT POSITION :\nX = %.2f\nY = %.2f\n", cursor_x_pos, cursor_y_pos);
  if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS && !combination
      && (cursor_x_pos <= window_width && cursor_y_pos <= window_height))
    output_on_screen("USER LEFT CLICKED INSIDE THE WINDOW\n");
  else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE && !combination)
    output_on_screen("USER RELEASED LEFT CLICK INSIDE THE WINDOW\n");
}

void key_callback([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scan_code,
                  int action, int combination)
{
  if (key == GLFW_KEY_F && action == GLFW_PRESS && !combination)
  {
    toggle_fullscreen(window);
  } else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && !combination)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

// Free resources and close the window.
void Window::cleanup()
{
  output_on_screen("DESTROYING WINDOW...\t");
  glfwDestroyWindow(window);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  output_on_screen("Done.\n", INFO, true);
}

void Window::set_callbacks(const Shader &program) const
{
  glfwSetWindowSizeCallback(window, window_viewport_callback);  // Change screen size event.
  glfwSetCursorPosCallback(window, cursor_position_callback);  // Change cursor position event.
  glfwSetCursorEnterCallback(window, cursor_enter_callback);  // Cursor in/out screen event.
  glfwSetMouseButtonCallback(window, mouse_button_callback);  // Mouse button input event.
  glfwSetScrollCallback(window, scroll_callback);  // Mouse scroll event.
  glfwSetKeyCallback(window, key_callback); // Key input events.
}
