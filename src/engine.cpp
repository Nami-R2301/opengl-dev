#include "../Include/engine.h"

Engine::Engine()
{
  this->frame_counter = 0;
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

gl_vertex_data_s Engine::get_data()
{
  return data;
}

void Engine::set_data(const gl_vertex_data_s &data_)
{
  this->data.vertex_source = data_.vertex_source;
  this->data.fragment_source = data_.fragment_source;
  this->data.vertices = data_.vertices;
}

void Engine::run()
{
  window.show();  // Show window content.
  Vertex *vertices = data.vertices.data();
  Shader program;
  program.add_shader(GL_VERTEX_SHADER, data.vertex_source);
  program.add_shader(GL_FRAGMENT_SHADER, data.fragment_source);
  program.link();

  this->game.init();

//  Vbo vertex_buffer_obj(vertices, (long) (sizeof(Vertex) * get_data().vertices.size()));
//  Vao vertex_array_obj;
//  vertex_array_obj.bind_vertex_array();
//  Evo evo(indices, sizeof(indices));
//  evo.bind();
//
//  Vao::link_attrib(0, 3, 7 * sizeof(float), (void *) nullptr);
//  Vao::link_attrib(1, 4, 7 * sizeof(float), (void *) (4 * sizeof(float)));
//
//  Vao::unbind_vertex_array();
//  Vbo::unbind();
//  Evo::unbind();

//  debug(vertices);
  double previous_time = Time::get_time();
  while (running_state)
  {
    double current_time = Time::get_time();
    frame_counter++;
    if (window.is_closed()) break;

    while ((current_time - previous_time) >= 1.0f && frame_counter <= (long) FRAME_CAP)
    {
      char title[sizeof(long) + 4];
      sprintf(title, "%ld FPS", frame_counter);
      glfwSetWindowTitle(window.get_window(), title);
      frame_counter = 0;
      previous_time = current_time;
    }
    render(program);
  }
  stop();
}

void Engine::render(Shader program)
{
  window.process_input();
  Color bg_color;
  Window::update_color(bg_color);
  program.activate(); // Specify what program to use.

  // Update fragment uniform
  double timeValue = glfwGetTime();
  Color color((float) (sin(timeValue / 2.0f)),
              (float) (sin(timeValue / 2.0f)),
              (float) (sin(timeValue / 2.0f)), 1.0f);
  if (color == Color(0.0f, 0.0f, 0.0f, 1.0f)) color = Color(1.0f, 1.0f, 1.0f, 1.0f);
  float scale = 0.10;
  program.update_color(color);  // Update object color.
  program.update_scale(scale);  //Update object scale.

  this->game.render();
  // Render our triangles.
//  vao.bind_vertex_array();
//  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr); // Draw from vertex arrays.
  glfwSwapBuffers(window.get_window()); // Update window buffer (refresh window).
  glfwSwapInterval(1);  // Disable/enable Vertical synchronisation (Vsync).
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
  printf("\nOpenGL Version : %d.%d.%d\n\n", Render::get_GL_version().major,
         Render::get_GL_version().minor,
         Render::get_GL_version().rev);
  Render::init_graphics();

  // Get shader sources and data.
  std::string vertex_source = get_shaders("../Resources/Shaders/default.vert");
  std::string fragment_source = get_shaders("../Resources/Shaders/default.frag");
  std::vector<Vertex> vertices = set_vertices_data();
  gl_vertex_data_s data = {vertex_source.c_str(), fragment_source.c_str(), vertices};

  // Run the engine.
  Engine game_engine;  // Initialize our game engine.
  // Get all relevant data for vertices and fragments.
  game_engine.set_data(data);
  game_engine.start();
  return 0;
}
