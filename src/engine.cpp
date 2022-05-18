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
  output_on_screen("------------STARTING UP ENGINE--------------\n");
  Render::init_graphics();  // Setup openGL graphic settings.
  Window::create_window();
  Window::set_callbacks(this->shader_program);  // Set our mouse and keyboard callbacks.
  Render::show_gl_info();  // Show info about opengl and glfw versions.
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
  start();  // Start and setup engine.
  this->shader_program.create_program();
  this->shader_program.add_shader(GL_VERTEX_SHADER, this->data.vertex_source);
  this->shader_program.add_shader(GL_FRAGMENT_SHADER, this->data.fragment_source);
  this->shader_program.link();
  this->game.init(this->data.vertices.data(), sizeof(Vertex) * get_data().vertices.size());
  output_on_screen("--------------------------------------------\n");
//  debug(vertices);

  auto previous_time = std::chrono::system_clock::now();
  while (!Window::is_closed())
  {
    auto current_time = std::chrono::system_clock::now();
    auto delta_time = current_time - previous_time;
    auto end_time = current_time + std::chrono::milliseconds(7);
    this->frame_counter++;
    if (Window::is_closed()) break;

    while (delta_time >= std::chrono::seconds(1) && this->frame_counter <= (long) MAX_FPS)
    {
      char title[sizeof(long) + 5];
      snprintf(title, sizeof(long) + 5, "%ld FPS", this->frame_counter);
      glfwSetWindowTitle(Window::get_window(), title);
      this->frame_counter = 0;
      previous_time = current_time;
    }
    render();
    std::this_thread::sleep_until(end_time);
  }
  stop();  // Terminate and cleanup.
}

void Engine::render()
{
  Window::clear_bg();  // Reset the background color on screen.
  this->shader_program.activate(); // Specify what program to use.

  // Update fragment uniform
  this->shader_program.update_color((float) (sin(glfwGetTime()) + .6),
                                    (float) (sin(glfwGetTime()) + .1),
                                    (float) (sin(glfwGetTime()) + .3), 1.0f);  // Update object color.
  this->shader_program.update_scale(0.20f);
  this->game.render();  // Render our graphics.
  Window::refresh(); // Refresh the window screen.
  glfwPollEvents(); // Listen and call the appropriate keyboard and mouse callbacks.
}

void Engine::stop()
{
  if (!this->running_state) return;
  this->running_state = false;
  cleanup();
}

void Engine::cleanup()
{
  output_on_screen("------------SHUTTING DOWN ENGINE------------\n");
  this->game.get_mesh().cleanup();
  this->shader_program = Shader();
  this->shader_program.delete_shaders(); // Delete all shaders.
  Window::cleanup();
  output_on_screen("TERMINATING GLFW...\t");
  glfwTerminate(); // Free resources and close all glfw windows and cursors.
  output_on_screen("Done.\n", INFO, true);
  output_on_screen("--------------------------------------------\n");
}

Engine::~Engine()
{
  if (this->running_state) cleanup();
}

void *Engine::operator new(unsigned long size)
{
  auto engine = (Engine *) malloc(size);
  if (engine == nullptr)
  {
    output_on_screen("NOT ENOUGH MEMORY ON THE HEAP\n", ERROR);
    exit(-11);
  }
  return engine;
}

void Engine::operator delete(void *engine)
{
  if (engine != nullptr) free(engine);
}

int main()
{
  int exit_code = 0;
  // Get shader sources and data.
  std::string vertex_source = Shader::get_shader_source("../Resources/Shaders/default.vert");
  std::string fragment_source = Shader::get_shader_source("../Resources/Shaders/default.frag");
  std::vector<Vertex> vertices = set_vertices_data();
  // Prepare data for shaders.
  gl_vertex_data_s data = {vertex_source.c_str(), fragment_source.c_str(), vertices};

  // Setup and start the engine.
  auto *game_engine = new Engine();
  game_engine->set_shader_data(data);  // Get all relevant data for vertices and fragments.
  game_engine->run();
  // In case of an unexpected crash.
  if (game_engine->get_running_state()) exit_code = UNEXPECTED_ERROR;
  delete game_engine;
  return exit_code;
}
