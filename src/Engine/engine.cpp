#include "engine.h"
#include "../OpenGL Graphics/window.h"
#include "../OpenGL Graphics/renderer.h"

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
  alert(INFO, "------------STARTING UP ENGINE--------------");
  init_graphics();  // Setup openGL graphic settings.
  Window::create_window();  // Make glfw context.
  this->game = new Game();  // Init game.
  show_gl_info();  // Show info about opengl and glfw versions.
  alert(INFO, "------------SUCCESSFULLY STARTED UP ENGINE--------------");
}

void Engine::run()
{
  start();  // Start and setup engine.
  alert(INFO, "------------RUNNING--------------");
  char title[sizeof(long) + 5];
  this->system_time.set_previous_time(std::chrono::system_clock::now());
  while (!Window::is_closed())
  {
    this->system_time.set_current_time(std::chrono::system_clock::now());
    if (!Window::is_closed()) render();
    set_frame_counter(this->frame_counter + 1);  // Increment fps.
    // Show how many fps were achieved if a second passed or if we rendered enough frames before the second passed.
    if (this->system_time.get_delta_time_chrono() >= std::chrono::seconds(1) ||
        this->frame_counter >= Window::get_refresh_rate())
    {
      snprintf(title, sizeof(title), "%ld FPS", get_frame_counter());
      glfwSetWindowTitle(Window::get_window(), title);

      set_frame_counter(0);  // Reset since the second has passed.
      this->system_time.set_previous_time(this->system_time.get_current_time());  // Count towards the next second.
    }
    glfwPollEvents(); // Listen and call the appropriate events.
  }
  alert(INFO, "------------STOPPING--------------");
  stop();  // Terminate and render_cleanup.
}

void Engine::render()
{
  Window::clear_bg();  // Reset the background color on screen.
  if (this->game == nullptr)
  {
    alert(ERROR, "FAILED TO INITIALIZE GAME IN GAME ENGINE ON LINE : 55!\tEXITING...");
    exit(-5);
  }
  this->game->input();  // Read and process game inputs.
  this->game->update();  // Update the game.
  this->game->render();  // Redraw on screen.
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
    alert(INFO, "------------SHUTTING DOWN ENGINE------------");
  else alert(ERROR, "------------FORCING SHUTDOWN OF ENGINE------------");
  Window::cleanup();
  alert(INFO, "SHUTTING DOWN GAME...");
  if (this->game) this->game->cleanup();
  delete get_game();
  alert(INFO, "SUCCESSFULLY SHUT DOWN GAME.");
  alert(INFO, "TERMINATING GLFW...");
  glfwTerminate(); // Free resources and close all glfw windows and cursors.
  if (get_exit_code() == 0)
    alert(INFO, "------------SUCCESSFULLY SHUT DOWN ENGINE------------");
  else alert(ERROR, "------------ENGINE SHUT DOWN UNEXPECTEDLY------------");
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
    alert(ERROR, "ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...");
    exit(ERROR_SNPRINTF);
  }
  alert(INFO, buffer);
  for (int i = 0; i < 6; ++i) vertices[i].print_vertex();
}

void *Engine::operator new(unsigned long size)
{
  open_file();  // Open logger stream for alerts.
  auto engine = (Engine *) malloc(size);
  if (engine == nullptr)
  {
    alert(ERROR, "NOT ENOUGH MEMORY ON THE HEAP");
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
      close_file();  // Close the stream for alerts.
      exit(exit_code);
    }
    engine_->cleanup();
    free(engine_);
  }
  close_file();  // Close the stream for alerts.
}

bool Engine::check_crash() const
{
  return get_exit_code() == NOT_FINISHED;  // In case of an unexpected crash.
}
