//
// Created by nami on 2022-02-23.
//

#include "../Include/window.h"

Window::Window()
{
  printf("CREATING WINDOW...");
  glfwInit(); //Initialize glfw

  monitor = glfwGetPrimaryMonitor(); // Get main monitor specs.
  mode = glfwGetVideoMode(monitor); // Get video specs of monitor.

  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

  // Hint at glfw our opengl version -> 3.3 -> [MAJOR].[MINOR] + that we have the core profile.
  // So that we will only use the modern functions in it.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Generate a pointer to a window using our monitor info, so that we later show it.
  window = glfwCreateWindow(mode->width, mode->height, "Main window",
                            nullptr, nullptr);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  printf("Done.\n");
}

// Free resources and close the window.
Window::~Window()
{
  glfwDestroyWindow(window);
  printf("DESTROYING WINDOW...\n");
}

// Show the window created.
void Window::show()
{
  if(!window)
  {
    printf("\n\nError creating window !\n\n");
    exit(-1);
  }
  glfwMakeContextCurrent(window); // Show our window.
  // Specify which coordinates to draw for our window -> from (0,0) to (monitor_width, monitor_height).
  glViewport(0, 0, mode->width, mode->height);
}

// Return a glfwWindow instance in case there's a need to manipulate the window directly.
GLFWwindow *Window::get_window() const
{
  return window;
}

// Let the window open as long as the close flag (gathered by glfwPollEvents) is not set to true.
bool Window::is_closed() const {
  return glfwWindowShouldClose(window);
}

void Window::update_color(Color &new_color) {
  rgb_color_s new_rgb_color = new_color.get_rgb_values();
  glClearColor(new_rgb_color.red, new_rgb_color.green, new_rgb_color.blue, new_rgb_color.alpha);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear and change the back buffer color bit with our color.
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback([[maybe_unused]] GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

