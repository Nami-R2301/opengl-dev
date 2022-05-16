#include "../Include/engine.h"

Engine::Engine()
{
  this->frame_counter = 0;
  this->running_state = false;
}

void Engine::start()
{
  if (this->running_state) return;
  this->running_state = true;
  printf("\n------------STARTING UP ENGINE--------------\n");
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
  this->window.create_window();  // Create the window.
  this->window.show();  // Show window content.
  Color bg_color;
  Window::update_color(bg_color);  // Set default background to dark-mode-like gray.
  Shader program;
  program.add_shader(GL_VERTEX_SHADER, this->data.vertex_source);
  program.add_shader(GL_FRAGMENT_SHADER, this->data.fragment_source);
  program.link();

  this->game.init(this->data.vertices.data(), sizeof(Vertex) * get_data().vertices.size());
  printf("--------------------------------------------\n");
//  debug(vertices);
  double previous_time = Time::get_time();
  while (this->running_state)
  {
    double current_time = Time::get_time();
    this->frame_counter++;
    if (this->window.is_closed()) break;

    while ((current_time - previous_time) >= 1.0f && this->frame_counter <= (long) FRAME_CAP)
    {
      char title[sizeof(long) + 4];
      sprintf(title, "%ld FPS", this->frame_counter);
      glfwSetWindowTitle(this->window.get_window(), title);
      this->frame_counter = 0;
      previous_time = current_time;
    }
    render(program);
  }
  stop(program);
}

void Engine::render(const Shader &program)
{
  Render::render_screen();  // Reset the screen.
  this->window.process_input();
  program.activate(); // Specify what program to use.

  // Update fragment uniform
  double timeValue = glfwGetTime();
  Color color((float) (sin(timeValue / 2.0f)),
              (float) (sin(timeValue / 2.0f)),
              (float) (sin(timeValue / 2.0f)), 1.0f);
  float scale = 0.10;
  program.update_color(color);  // Update object color.
  program.update_scale(scale);  //Update object scale.

  this->game.render();  // Render our graphics on screen.
  glfwSwapBuffers(this->window.get_window()); // Update window buffer (refresh window).
  glfwSwapInterval(1);  // Disable/enable Vertical synchronisation (Vsync).
  glfwPollEvents(); // Take care of our events.
}

void Engine::stop(const Shader &shader_program)
{
  if (!this->running_state) return;
  this->running_state = false;
  cleanup(shader_program);
}

void Engine::cleanup(const Shader &shader_program)
{
  printf("------------SHUTTING DOWN ENGINE------------\n");
  this->game.get_mesh().cleanup();
  shader_program.delete_shaders(); // Delete all shaders.
  printf("TERMINATING GLFW...\t");
  glfwTerminate(); // Free resources and close all glfw windows and cursors.
  printf("Done.\n");
  this->window.cleanup();
  printf("--------------------------------------------\n");
}

Engine::~Engine()
{
  if (this->running_state) cleanup();
}

int main()
{
  Render::init_graphics();  // Setup openGL graphic settings.

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
  if (game_engine.get_running_state()) return -10;
  return 0;
}
