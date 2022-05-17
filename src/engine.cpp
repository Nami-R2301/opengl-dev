#include "../Include/engine.h"

#define UNEXPECTED_ERROR 222

Engine::Engine()
{
  this->frame_counter = 0;
  this->running_state = false;
}

void Engine::start()
{
  if (this->running_state) return;
  this->running_state = true;
  output_on_screen("------------STARTING UP ENGINE--------------\n");
  Render::init_graphics();  // Setup openGL graphic settings.
  this->window.create_window();
  Render::show_gl_info();  // Show info about opengl and glfw versions.
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
  return this->data;
}

bool Engine::get_running_state() const
{
  return this->running_state;
}

void Engine::set_shader_data(const gl_vertex_data_s &data_)
{
  this->data.vertex_source = data_.vertex_source;
  this->data.fragment_source = data_.fragment_source;
  this->data.vertices = data_.vertices;
}

void Engine::run()
{
  Color bg_color;
  Window::update_color(bg_color);  // Set default background to dark-mode-like gray.
  Shader program;
  program.add_shader(GL_VERTEX_SHADER, this->data.vertex_source);
  program.add_shader(GL_FRAGMENT_SHADER, this->data.fragment_source);
  program.link();

  this->game.init(this->data.vertices.data(), sizeof(Vertex) * get_data().vertices.size());
  output_on_screen("--------------------------------------------\n");
//  debug(vertices);
  double previous_time = Time::get_game_time();
  bool is_rendering = true;
  while (is_rendering)
  {
    double current_time = Time::get_game_time();
    this->frame_counter++;
    if (this->window.is_closed()) is_rendering = false;

    while ((current_time - previous_time) >= 1.0f && this->frame_counter <= (long) FRAME_CAP)
    {
      char title[sizeof(long) + 5];
      snprintf(title, sizeof(long) + 5, "%ld FPS", this->frame_counter);
      glfwSetWindowTitle(this->window.get_window(), title);
      this->frame_counter = 0;
      previous_time = current_time;
    }
    if (is_rendering) render(program, bg_color);
    else stop(program);
  }
}

void Engine::render(const Shader &program, Color &color)
{
  Render::reset();  // Reset the color on screen.
  program.activate(); // Specify what program to use.

  // Update fragment uniform
  color.set_color((float) (sin(glfwGetTime()) + .6),
                  (float) (sin(glfwGetTime()) + .1),
                  (float) (sin(glfwGetTime()) + .3), 1.0f);
  program.update_color(color);  // Update object color.
  program.update_scale(0.20f);
  this->game.render();  // Render our graphics.
  this->window.refresh(); // Refresh the window screen.
  glfwPollEvents(); // Listen and call the appropriate keyboard and mouse callbacks.
}

void Engine::stop(const Shader &shader_program)
{
  if (!this->running_state) return;
  this->running_state = false;
  cleanup(shader_program);
}

void Engine::cleanup(const Shader &shader_program)
{
  output_on_screen("------------SHUTTING DOWN ENGINE------------\n");
  this->game.get_mesh().cleanup();
  shader_program.delete_shaders(); // Delete all shaders.
  this->window.cleanup();
  output_on_screen("TERMINATING GLFW...\t");
  glfwTerminate(); // Free resources and close all glfw windows and cursors.
  output_on_screen("Done.\n", INFO, true);
  output_on_screen("--------------------------------------------\n");
}

Engine::~Engine()
{
  if (this->running_state) cleanup();
}

[[maybe_unused]] const Window &Engine::get_window() const
{
  return window;
}

[[maybe_unused]] void Engine::set_window(const Window &window_)
{
  this->window = window_;
}

int main()
{
  // Get shader sources and data.
  std::string vertex_source = Shader::get_shader_source("../Resources/Shaders/default.vert");
  std::string fragment_source = Shader::get_shader_source("../Resources/Shaders/default.frag");
  std::vector<Vertex> vertices = set_vertices_data();
  // Prepare data for shaders.
  gl_vertex_data_s data = {vertex_source.c_str(), fragment_source.c_str(), vertices};

  // Setup and start the engine.
  Engine game_engine;  // Initialize our game engine.
  game_engine.set_shader_data(data);  // Get all relevant data for vertices and fragments.
  game_engine.start();

  // In case of an unexpected crash.
  if (game_engine.get_running_state()) return UNEXPECTED_ERROR;
  return 0;
}
