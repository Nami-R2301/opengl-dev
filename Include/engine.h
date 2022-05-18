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

#define MAX_FPS 144.0
#define UNEXPECTED_ERROR 222

typedef struct gl_data_s
{
  const char *vertex_source = nullptr;
  const char *fragment_source = nullptr;
  std::vector<Vertex> vertices;
} gl_vertex_data_s;

class Engine
{
public:
  Engine();
  ~Engine();
  [[nodiscard]] bool get_running_state() const;
  gl_vertex_data_s get_data();
  void set_shader_data(const gl_vertex_data_s &data);
  void run();
  [[maybe_unused]] static void debug(Vertex *data);
  void *operator new(unsigned long size);
  void operator delete(void *color);
private:
  Game game;
  Shader shader_program;
  gl_vertex_data_s data;
  bool running_state;
  long frame_counter;
  const double max_period = 1 / MAX_FPS;
  void start();
  void render();
  void stop();
  void cleanup();
};

#endif //OPENGL_DEV_ENGINE_H

