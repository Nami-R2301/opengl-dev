//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_ENGINE_H
#define OPENGL_DEV_ENGINE_H

#include "../Game logic/game.h"

#define NOT_FINISHED 223
#define CRASH 224
#define GAME_CRASH -5

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
  Game *game = nullptr;
  Game_time system_time;
  bool running_state;
  long frame_counter;
  int exit_code = NOT_FINISHED;  // Document the m_renderer_id exit code for maintenance.

  [[maybe_unused]] void set_game(Game *game_);
  [[nodiscard]] bool check_crash() const;

  void set_frame_counter(long counter);
  void set_running_state(bool new_state);
  void set_exit_code(int code);
  void start();
  void render();
  void stop();
  void force_stop();
  void cleanup() const;
};

#endif //OPENGL_DEV_ENGINE_H

