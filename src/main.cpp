#include "../Include/main.h"
#include "../Include/constants.h"
#include "../Include/evo.h"
#include <GLFW/glfw3.h>

int main()
{
  Window gl_window; //Initialize window.
  Color bg_color; //Background color of the window.
  gl_window.show(); // Show window.
  printf("size of rgb_color_s : %lu\n\n", sizeof(float));
  fflush(stdout);
  printf("Vertex colors : %d\n");

  Shader vertex_shader(GL_VERTEX_SHADER);
  vertex_shader.source(1, vertex_source.c_str(), nullptr);
  vertex_shader.compile();
  Shader fragment_shader(GL_FRAGMENT_SHADER);
  fragment_shader.source(1, fragment_source.c_str(), nullptr);
  fragment_shader.compile();

  Program shader_program;
  shader_program.attach(vertex_shader);
  shader_program.attach(fragment_shader);
  shader_program.link();

  Vao vertex_array_obj;
  Vbo vertex_buffer_obj(vertices, sizeof(vertices));
  vertex_array_obj.bind_vertex_array();
  Evo evo(indices, sizeof(indices));

  vertex_array_obj.link_attrib(vertex_buffer_obj, 0,3, 7 * sizeof(float),
                               (void*) 0);
  vertex_array_obj.link_attrib(vertex_buffer_obj, 1, 4, 7 * sizeof(float),
                               (void*)(3 * sizeof(float)));

  vertex_array_obj.unbind_vertex_array();
  vertex_buffer_obj.unbind();
  evo.unbind();

  int id = glGetUniformLocation(shader_program.get_program(), "scale");

  while(!gl_window.is_closed())
  {
    bg_color.clear();
    gl_window.update_color(bg_color);
    shader_program.activate(); // Specify what program to use.
    glUniform1f(id, 0.5f);
    vertex_array_obj.bind_vertex_array();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.

    glfwSwapBuffers(gl_window.get_window()); // Update window buffer (refresh window).
    glfwPollEvents(); // Take care of our events.
  }
  glfwTerminate(); // Free resources and close all glfw widows and cursors.
  return 0;
}

