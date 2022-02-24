#include "../Include/main.h"
#include "../Include/constants.h"
#include <GLFW/glfw3.h>

int main()
{
  Window gl_window; //Initialize window.
  Color bg_color; //Background color of the window.
  gl_window.show(); // Show window.
  gl_data_t data = compute_data(); // Get all relevant data for vertices and fragments.
  debug(data.vertices); // For debugging purposes.

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
  Vbo vertex_buffer_obj(data.vertices, sizeof(Vertex) * 6);
  vertex_array_obj.bind_vertex_array();
  Evo evo(indices, sizeof(indices));

  vertex_array_obj.link_attrib(vertex_buffer_obj, 0,3, 7 * sizeof(float),
                               (void*) nullptr);
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

gl_data_t compute_data()
{
  const Color vertex_colors(1.0f, 0.84f, 0.00f, 1.0); // Default color for fragments.

  // Coordinates (x,y,z)                                          // Colors (RGB).
  Vertex a(-0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower left corner.
  Vertex b(0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower right corner.
  Vertex c(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, vertex_colors); // Upper corner.
  Vertex d(-0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner left.
  Vertex e(0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); //Inner right.
  Vertex f(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner down.

  // Create our GLfloat vertices to pass on to the buffers.
  Vertex vertices[6] = {a, b, c, d, e, f};
  Vertex (*new_vertices)[6] = &vertices;
  debug(vertices);

  gl_data_t data = {vertex_source.c_str(), fragment_source.c_str(),
                    (Vertex*) new_vertices};
  return data;
}

void debug(Vertex* vertices)
{
  printf("size of rgb_color_s : %lu\n\n",sizeof(*vertices));
  fflush(stdout);
  for(int i = 0; i < 6; ++i) vertices[i].print_vertex();
}

