//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_ENGINE_H
#define OPENGL_DEV_ENGINE_H

#include "OpenGL Graphics/vertex_test.h"
#include "OpenGL Graphics/mesh.h"
#include "Game logic/game.h"
#include "OpenGL Graphics/shader.h"
#include "OpenGL Graphics/window.h"
#include "Logs/logger.h"

//TODO: Change max fps to reasonable amount when in production.
#define MAX_FPS 144L
#define MILI_SECONDS 1000L
#define NOT_FINISHED 223
#define CRASH 224

class Engine
{
public:
  Engine();
  [[nodiscard]] Game *get_game() const;
  [[nodiscard]] long get_frame_counter() const;
  [[nodiscard]] bool get_running_state() const;
  [[nodiscard]] int get_exit_code() const;

  void run();
  [[maybe_unused]] static void debug(Vertex *data);

  void *operator new(unsigned long size);
  void operator delete(void *engine);
private:
  Game *game = new Game();
  gl_vertex_data_s data;
  bool running_state;
  long frame_counter;
  int exit_code = NOT_FINISHED;  // Document the program exit code for maintenance.
  const double time_per_frame = ((1.0f * MILI_SECONDS) / (double) MAX_FPS);  // Approx. 6.94 ms.

  [[maybe_unused]] void set_game(Game *game_);
  void set_frame_counter(long counter);
  void set_running_state(bool new_state);
  void set_exit_code(int code);
  void start();
  void render();
  void stop();
  [[nodiscard]] bool check_crash() const;
  void force_stop();
  void cleanup() const;
};

#endif //OPENGL_DEV_ENGINE_H

