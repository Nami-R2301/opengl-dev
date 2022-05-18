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
#define MAX_FPS 10000L
#define UNEXPECTED_ERROR 222

class Engine
{
public:
  Engine();
  [[nodiscard]] bool get_running_state() const;
  void run();
  int force_stop();
  [[maybe_unused]] static void debug(Vertex *data);
  void *operator new(unsigned long size);
  void operator delete(void *color);
private:
  Game game;
  gl_vertex_data_s data;
  bool running_state;
  long frame_counter;
  void start();
  void render();
  void stop();
  void cleanup();
};

#endif //OPENGL_DEV_ENGINE_H

