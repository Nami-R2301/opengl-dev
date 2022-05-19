#include "../Include/engine.h"

Engine::Engine()
{
  this->frame_counter = 0;
  this->running_state = false;
}

Game *Engine::get_game() const
{
  return this->game;
}

long Engine::get_frame_counter() const
{
  return this->frame_counter;
}

bool Engine::get_running_state() const
{
  return this->running_state;
}

int Engine::get_exit_code() const
{
  return this->exit_code;
}

[[maybe_unused]] void Engine::set_game(Game *game_)
{
  this->game = game_;
}

void Engine::set_frame_counter(long counter)
{
  this->frame_counter = counter;
}

void Engine::set_running_state(bool new_state)
{
  this->running_state = new_state;
}

void Engine::set_exit_code(int code)
{
  this->exit_code = code;
}

void Engine::start()
{
  if (this->running_state) return;
  set_running_state(true);
  Logger::alert("------------STARTING UP ENGINE--------------\n");
  Render::init_graphics();  // Setup openGL graphic settings.
  Window::create_window();
  Window::set_callbacks();  // Set our mouse and keyboard callbacks.
  Render::show_gl_info();  // Show info about opengl and glfw versions.
  this->game->prepare_mesh();
  Logger::alert("------------SUCCESSFULLY STARTED UP ENGINE--------------\n");
}

void Engine::run()
{
  start();  // Start and setup engine.
  Logger::alert("------------RUNNING--------------\n");
  char title[sizeof(long) + 5];
  auto previous_time = std::chrono::system_clock::now();
  while (!Window::is_closed())
  {
    auto current_time = std::chrono::system_clock::now();
    set_frame_counter(this->frame_counter + 1);  // Increment fps.
    if (current_time - previous_time >= std::chrono::seconds(1))  // Show how many fps were achieved.
    {
      if (this->frame_counter >= (1 * MILI_SECONDS / MAX_FPS))  // More than 144 fps.
      {
        snprintf(title, sizeof(title), "%ld FPS\n", get_frame_counter());
        Logger::alert(title);
        title[strlen(title) - 1] = '\0';  // Remove newline for window title.
        glfwSetWindowTitle(Window::get_window(), title);
      }
      set_frame_counter(0);  // Reset since the second has passed.
      previous_time = current_time;  // Count towards the next second.
    }
    if (!Window::is_closed()) render();
    glfwPollEvents(); // Listen and call the appropriate keyboard and mouse callbacks.
  }
  Logger::alert("------------STOPPING--------------\n");
  stop();  // Terminate and cleanup.
}

void Engine::render()
{
  Window::clear_bg();  // Reset the background color on screen.
  this->game->update();  // Update the game.
  this->game->draw();  // Redraw on screen.
  Window::refresh(); // Refresh the window screen.
}

void Engine::stop()
{
  if (get_running_state()) set_running_state(false);
  set_exit_code(0);
}

void Engine::cleanup() const
{
  if (get_exit_code() == 0)
    Logger::alert("------------SHUTTING DOWN ENGINE------------\n");
  else Logger::alert("------------FORCING SHUTDOWN OF ENGINE------------\n");
  Window::cleanup();
  Logger::alert("SHUTTING DOWN GAME...\n");
  this->game->cleanup();
  delete get_game();
  Logger::alert("SUCCESSFULLY SHUT DOWN GAME.\n");
  Logger::alert("TERMINATING GLFW...\t");
  glfwTerminate(); // Free resources and close all glfw windows and cursors.
  Logger::alert("Done.\n", INFO, true);
  if (get_exit_code() == 0)
    Logger::alert("------------SUCCESSFULLY SHUT DOWN ENGINE------------\n");
  else Logger::alert("------------ENGINE SHUT DOWN UNEXPECTEDLY------------\n");
}

void Engine::force_stop()
{
  set_exit_code(CRASH);
  cleanup();
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

void *Engine::operator new(unsigned long size)
{
  Logger::open_file();  // Open logger stream for alerts.
  auto engine = (Engine *) malloc(size);
  if (engine == nullptr)
  {
    Logger::alert("NOT ENOUGH MEMORY ON THE HEAP\n", ERROR);
    exit(ERROR_HEAP_ALLOC);
  }
  return engine;
}

void Engine::operator delete(void *engine)
{
  auto engine_ = (Engine *) engine;
  if (engine != nullptr)
  {
    if (engine_->check_crash())
    {
      int exit_code = engine_->get_exit_code();
      engine_->force_stop();
      free(engine_);
      Logger::close_file();  // Close the stream for alerts.
      exit(exit_code);
    }
    engine_->cleanup();
    free(engine_);
  }
  Logger::close_file();  // Close the stream for alerts.
}

bool Engine::check_crash() const
{
  return get_exit_code() == NOT_FINISHED;  // In case of an unexpected crash.
}

int main()
{
  // Setup and start the engine.
  auto *game_engine = new Engine();
  game_engine->run();  // Run game.
  delete game_engine;  // Cleanup procedure and deallocate all resources from heap.
  return 0;
}
