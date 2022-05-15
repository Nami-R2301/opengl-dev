//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_ENGINE_H
#define OPENGL_DEV_ENGINE_H

#include "window.h"
#include "OpenGL Graphics/vertex_test.h"
#include "OpenGL Graphics/vao.h"
#include "OpenGL Graphics/vbo.h"
#include "OpenGL Graphics/evo.h"
#include "OpenGL Graphics/constants.h"
#include "Game logic/game_time.h"
#include "OpenGL Graphics/mesh.h"
#include "Game logic/game.h"
#include <cmath>

#define FRAME_CAP 10000.0

typedef struct gl_data_s
{
  const char *vertex_source = nullptr;
  const char *fragment_source = nullptr;
  std::vector<Vertex> vertices;
} gl_vertex_data_s;

class Engine
{
public:
  explicit Engine();
  gl_vertex_data_s get_data();
  void set_data(const gl_vertex_data_s &data);
  void start();
  void stop();
  [[maybe_unused]] static void debug(Vertex *data);
private:
  Game game;
  Window window;
  gl_vertex_data_s data;
  bool running_state;
  long frame_counter;
  void run();
  void render(Shader program);
  static void cleanup();
};

#endif //OPENGL_DEV_ENGINE_H

