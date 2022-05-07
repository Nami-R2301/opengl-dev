#include "../Include/main.h"

int main()
{
  glfwInit(); //Initialize glfw
  Window gl_window; //Initialize window.
  Color bg_color; //Background color of the window.
  gl_window.show(); // Show window.
  std::string vertex_source = get_shaders("../Resources/Shaders/default.vert");
  std::string fragment_source = get_shaders("../Resources/Shaders/default.frag");
  gl_data_s data = compute_data(vertex_source.c_str(),
                                fragment_source.c_str()); // Get all relevant data for vertices and fragments.
  Vertex *vertices = data.vertices.data();
  Shader vertex_shader(GL_VERTEX_SHADER, data.vertex_source);
  Shader fragment_shader(GL_FRAGMENT_SHADER, data.fragment_source);

  Program shader_program;
  shader_program.attach(vertex_shader);
  shader_program.attach(fragment_shader);
  shader_program.link();
  shader_program.validate();

  Vao vertex_array_obj;
  Vbo vertex_buffer_obj(vertices, (long) (sizeof(Vertex) * data.vertices.size()));
  vertex_array_obj.bind_vertex_array();
  Evo evo(indices, sizeof(indices));
  evo.bind();

  Vao::link_attrib(0, 3, 7 * sizeof(float), (void *) nullptr);
  Vao::link_attrib(1, 4, 7 * sizeof(float), (void *) (4 * sizeof(float)));

  Vao::unbind_vertex_array();
  Vbo::unbind();
  Evo::unbind();

  while (!gl_window.is_closed()) {
    gl_window.process_input();
    bg_color.clear();
    Window::update_color(bg_color);
    shader_program.activate(); // Specify what program to use.

    // Update fragment uniform
    double timeValue = glfwGetTime();
    Color color((float) (cos(timeValue) / 2.0 + 0.6),
                (float) (cos(timeValue) / 2.0 + 0.6),
                (float) (cos(timeValue) / 2.0 + 0.6), 1.0f);
    float scale = 0.25;
    shader_program.update_color(color);
    shader_program.update_scale(scale);

    // Render our triangle.
    vertex_array_obj.bind_vertex_array();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.

    glfwSwapBuffers(gl_window.get_window()); // Update window buffer (refresh window).
    glfwPollEvents(); // Take care of our events.
  }
  glfwTerminate(); // Free resources and close all glfw widows and cursors.
  return 0;
}

gl_data_t compute_data(const char *vertex_source, const char *fragment_source) {
  const Color vertex_colors(0.25f, 0.84f, 0.5f, 1.0f); // Default color for fragments.

  // Coordinates (x,y,z)                                          // Colors (RGB).
  Vertex a(-0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower left corner.
  Vertex b(0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower right corner.
  Vertex c(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, vertex_colors); // Upper corner.
  Vertex d(-0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner left.
  Vertex e(0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); //Inner right.
  Vertex f(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner down.

  // Create our GLfloat vertices to pass on to the buffers.
  std::vector<Vertex> vertices;
  vertices.push_back(a), vertices.push_back(b), vertices.push_back(c),
      vertices.push_back(d), vertices.push_back(e), vertices.push_back(f);
  debug(vertices.data()); // For debugging purposes.

  gl_data_t data = {vertex_source, fragment_source, vertices};
  return data;
}

void debug(Vertex *vertices)
{
  fflush(stdout);
  printf("size of rgb_color_s : %lu\n\n", sizeof(*vertices));
  for (int i = 0; i < 6; ++i) vertices[i].print_vertex();
}

