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
  Logger::alert("------------STARTING UP ENGINE--------------\n");
  Render::init_graphics();  // Setup openGL graphic settings.
  Window::create_window();
  Window::set_callbacks(this->game.get_program());  // Set our mouse and keyboard callbacks.
  Render::show_gl_info();  // Show info about opengl and glfw versions.
  Logger::alert("------------SUCCESSFULLY STARTED UP ENGINE--------------\n");
}

[[maybe_unused]] void Engine::debug(Vertex *vertices)
{
  char buffer[1024];
  if (snprintf(buffer, 256, "size of rgb_color_s : %lu\n\n", sizeof(*vertices)) < 0)
  {
    Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
    exit(ERROR_SNPRINTF);
  }
  Logger::alert(buffer);
  for (int i = 0; i < 6; ++i) vertices[i].print_vertex();
}

bool Engine::get_running_state() const
{
  return this->running_state;
}

void Engine::run()
{
  start();  // Start and setup engine.
  Logger::alert("------------PREPARING GRAPHICS--------------\n");
  this->game.prepare_mesh();
  Logger::alert("------------SUCCESSFULLY LOADED GRAPHICS--------------\n");
//  debug(vertices);

  Logger::alert("------------RUNNING--------------\n");
  auto previous_time = std::chrono::system_clock::now();
  while (!Window::is_closed())
  {
    auto current_time = std::chrono::system_clock::now();
    this->frame_counter++;
    if (Window::is_closed()) break;
    if (current_time - previous_time >= std::chrono::seconds(1) && this->frame_counter <= MAX_FPS + 5)
    {
      char title[sizeof(long) + 5];
      snprintf(title, sizeof(title), "%ld FPS\n", this->frame_counter);
      Logger::alert(title);
      char window_title[sizeof(long) + 4];
      snprintf(window_title, sizeof(window_title), "%ld FPS", this->frame_counter);
      glfwSetWindowTitle(Window::get_window(), window_title);
      this->frame_counter = 0;
      previous_time = current_time;
    }
    render();
  }
  Logger::alert("------------STOPPING--------------\n");
  stop();  // Terminate and cleanup.
}

void Engine::render()
{
  Window::clear_bg();  // Reset the background color on screen.
  this->game.get_program().activate(); // Specify what program to use.

  // Update fragment_source uniform
  this->game.get_program().update_color((float) (sin(glfwGetTime()) + .6),
                                        (float) (sin(glfwGetTime()) + .1),
                                        (float) (sin(glfwGetTime()) + .3), 1.0f);  // Update object color.
  this->game.get_program().update_scale(0.20f);
  this->game.render();  // Render our graphics.
  Window::refresh(); // Refresh the window screen.
  glfwPollEvents(); // Listen and call the appropriate keyboard and mouse callbacks.
}

void Engine::stop()
{
  this->running_state = false;
  cleanup();
}

void Engine::cleanup()
{
  Logger::alert("------------SHUTTING DOWN ENGINE------------\n");
  this->game.get_mesh().cleanup();
  Window::cleanup();
  this->game.get_program().delete_shader(); // Delete shaders.
  Logger::alert("TERMINATING GLFW...\t");
  glfwTerminate(); // Free resources and close all glfw windows and cursors.
  Logger::alert("Done.\n", INFO, true);
  Logger::alert("------------SUCCESSFULLY SHUT DOWN ENGINE------------\n");
}

void *Engine::operator new(unsigned long size)
{
  auto engine = (Engine *) malloc(size);
  if (engine == nullptr)
  {
    Logger::alert("NOT ENOUGH MEMORY ON THE HEAP\n", ERROR);
    exit(-11);
  }
  return engine;
}

void Engine::operator delete(void *engine)
{
  if (engine != nullptr) free(engine);
}

int Engine::force_stop()
{
  cleanup();
  return UNEXPECTED_ERROR;
}

int main()
{
  int exit_code = 0;  // Document the program exit code for maintenance.
  Logger::open_file();  // Open logger stream for alerts.

  // Setup and start the engine.
  auto *game_engine = new Engine();
  game_engine->run();  // Execute everything.

  if (game_engine->get_running_state()) exit_code = game_engine->force_stop();  // In case of an unexpected crash.
  delete game_engine;
  Logger::close_file();  // Close the stream for alerts.
  return exit_code;
}
