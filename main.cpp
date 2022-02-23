#include <iostream>
#include "main.h"
#include <GLFW/glfw3.h>
#include <cmath>

int main()
{
  glfwInit(); //Initialize glfw

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(monitor);

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
  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, "Main window",
                                        nullptr, nullptr);
  if(!window)
  {
    printf("\n\nError creating window !\n\n");
    exit(-1);
  }
  glfwMakeContextCurrent(window); // Show our window.
  // Specify which coordinates to draw for our window -> from (0,0) to (monitor_width, monitor_height).
  glViewport(0, 0, mode->width, mode->height);

  // Create our GLfloat vertices to pass on to the buffers.
  gl_vertex_t vertices[] =
      {
          -0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner.
          0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner.
          0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner.
          -0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, // Inner left.
          0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, //Inner right.
          0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down.
      };

  GLuint indices[] =
      {
          0, 3, 5, // Lower left triangle.
          5, 4, 1, // Lower right triangle.
          3, 2, 4 // Upper triangle.
      };

  // Create Shaders for our vertex buffer object (VBO).
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

  //Set the source code in shader to the source code in the array of strings specified by string.
  glShaderSource(vertex_shader, 1, &vertexShaderSource, nullptr);
  glShaderSource(fragment_shader, 1, &fragmentShaderSource, nullptr);
  // Compile the shaders into machine code to pass on to the GPU.
  glCompileShader(fragment_shader);
  glCompileShader(vertex_shader);

  // Set our shader program to attach our created shader to it (link source codes like '#include').
  GLuint shader_program = glCreateProgram(); // Creates an empty object program (.o).
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);

  // Links all source codes (shaders) in the program given as argument, creating the executable.
  glLinkProgram(shader_program);

  // Delete the shaders since they have been compiled and linked in the program.
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  // Create vertex objects to contain and wrap our data to transfer data following opengl conventions.
  GLuint vertex_array_obj, vertex_buffer_obj, evo;
  glGenVertexArrays(1, &vertex_array_obj);
  glGenBuffers(1, &vertex_buffer_obj); // Create empty buffer for our vertex data.
  glGenBuffers(1, &evo);

  // Make the VAO the current Vertex Array Object by binding it
  glBindVertexArray(vertex_array_obj);
  glBindBuffer(GL_ARRAY_BUFFER,
               vertex_buffer_obj); // Bind it to an array containing multiple VBOs.
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Specify the data.
  // Specify the attribute of the vertex data to create a vertex attribute array for rendering data.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, evo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // Arguments serve to specify the number, type and stride (number of bytes to 'hop' between data).
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
  glEnableVertexAttribArray(
      0); // Enable our vertex attribute array and set the initial index cursor.

  // Unbind our vertex objects to prevent further usage of these buffers.
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Variables to be changed in the ImGUI window
  float size = 1.0f;
  float color[4] = {0.9f, 0.6f, 0.02f, 1.0f};

  // Exporting variables to shaders
  glUseProgram(shader_program);
  glUniform1f(glGetUniformLocation(shader_program, "size"), size);
  glUniform4f(glGetUniformLocation(shader_program, "color"), color[0], color[1], color[2],
              color[3]);

  // Let the window open as long as the close flag (gathered by glfwPollEvents) is not set to true.
  while(!glfwWindowShouldClose(window))
  {
    glClearColor(0.156862745f, 0.156862745f, 0.156862745f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Clear and change the back buffer color bit with our color.
    glUseProgram(shader_program); // Specify what program to use.
    glBindVertexArray(vertex_array_obj);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.

    // Export variables to shader.
    glUseProgram(shader_program);
    glUniform1f(glGetUniformLocation(shader_program, "size"), size);
    glUniform4f(glGetUniformLocation(shader_program, "color"), color[0], color[1], color[2],
                color[3]);

    glfwSwapBuffers(window); // Update window buffer (refresh window).
    glfwPollEvents(); // Take care of our events.
  }

  // Delete and free up memory to properly close our program, vertex buffers, and vertex arrays.
  glDeleteVertexArrays(1, &vertex_array_obj);
  glDeleteBuffers(1, &vertex_buffer_obj);
  glDeleteBuffers(1, &evo);
  glDeleteProgram(shader_program);
  glfwDestroyWindow(window); // Free resources and close the window.
  glfwTerminate(); // Free resources and close all glfw widows and cursors.
  return 0;
}

