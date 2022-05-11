#include "../Include/engine.h"
#include "../Include/vertex_test.h"

Engine::Engine()
{
  this->running_state = false;
}

void Engine::start()
{
  if (running_state) return;
  running_state = true;
  run();
}

[[maybe_unused]] void Engine::debug(Vertex *vertices)
{
  fflush(stdout);
  printf("size of rgb_color_s : %lu\n\n", sizeof(*vertices));
  for (int i = 0; i < 6; ++i) vertices[i].print_vertex();
}

gl_data_t Engine::get_data()
{
  return data;
}

void Engine::set_data(const gl_data_t &data_)
{
  this->data.vertex_source = data_.vertex_source;
  this->data.fragment_source = data_.fragment_source;
  this->data.vertices = data_.vertices;
}

void Engine::run()
{
  Color bg_color;  // Default background color of the window.
  window.show();  // Show window content.
  Vertex *vertices = data.vertices.data();
  Shader vertex_shader(GL_VERTEX_SHADER, data.vertex_source);
  Shader fragment_shader(GL_FRAGMENT_SHADER, data.fragment_source);

  Program shader_program;
  shader_program.attach(vertex_shader);
  shader_program.attach(fragment_shader);
  shader_program.link();
  shader_program.validate();

  Vao vertex_array_obj;
  Vbo vertex_buffer_obj(vertices, (long) (sizeof(Vertex) * get_data().vertices.size()));
  vertex_array_obj.bind_vertex_array();
  Evo evo(indices, sizeof(indices));
  evo.bind();

  Vao::link_attrib(0, 3, 7 * sizeof(float), (void *) nullptr);
  Vao::link_attrib(1, 4, 7 * sizeof(float), (void *) (4 * sizeof(float)));

  Vao::unbind_vertex_array();
  Vbo::unbind();
  Evo::unbind();

  debug(vertices);
  while (!window.is_closed())
  {
    clock_t begin_frame = clock();
    render(bg_color, shader_program, vertex_array_obj);
    clock_t end_frame = clock();
    printf("Delta_time : %.2ld\n", end_frame - begin_frame);
  }
  stop();
}

void Engine::render(Color bg_color, const Program &shader_program, const Vao &vertex_array_obj)
{
  window.process_input();
  bg_color.clear();
  Window::update_color(bg_color);
  shader_program.activate(); // Specify what program to use.

  // Update fragment uniform
  double timeValue = glfwGetTime();
  Color color((float) (sin(timeValue / 2.0f)),
              (float) (sin(timeValue / 2.0f)),
              (float) (sin(timeValue / 2.0f)), 1.0f);
  if (color == Color(0.0f, 0.0f, 0.0f, 1.0f)) color = Color(1.0f, 1.0f, 1.0f, 1.0f);
  float scale = 0.15;
  shader_program.update_color(color);  // Update object color.
  shader_program.update_scale(scale);  //Update object scale.

  // Render our triangle.
  vertex_array_obj.bind_vertex_array();
  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.

  glfwSwapBuffers(window.get_window()); // Update window buffer (refresh window).
  glfwPollEvents(); // Take care of our events.
}

void Engine::stop()
{
  if (!running_state) return;
  running_state = false;
  cleanup();
}

void Engine::cleanup()
{
  glfwTerminate(); // Free resources and close all glfw widows and cursors.
}

int main()
{
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR : FAILED TO INITIALIZE GLFW"); //Initialize glfw
    exit(-1);
  }
  std::string vertex_source = get_shaders("../Resources/Shaders/default.vert");
  std::string fragment_source = get_shaders("../Resources/Shaders/default.frag");
  std::vector<Vertex> vertices = set_vertices_data();
  gl_data_t data = {vertex_source.c_str(), fragment_source.c_str(), vertices};

  Engine game_engine;  // Initialize our game engine.
  // Get all relevant data for vertices and fragments.
  game_engine.set_data(data);
  game_engine.start();
  return 0;
}
