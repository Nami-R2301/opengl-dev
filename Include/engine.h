//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_ENGINE_H
#define OPENGL_DEV_ENGINE_H

#include "window.h"
#include "OpenGL Graphics/vertex_test.h"
#include "OpenGL Graphics/program.h"
#include "OpenGL Graphics/vao.h"
#include "OpenGL Graphics/vbo.h"
#include "OpenGL Graphics/evo.h"
#include "OpenGL Graphics/constants.h"
#include "Game logic/game_time.h"
#include "OpenGL Graphics/mesh.h"
#include <cmath>

#define FRAME_CAP 5000.0

typedef struct gl_data_s
{
  const char *vertex_source = nullptr;
  const char *fragment_source = nullptr;
  std::vector<Vertex> vertices;
} gl_vertex_data_s;

typedef struct gl_shader_data_s
{
  Shader vertex_shader;
  Shader fragment_shader;
  Program program;
  Vao vertex_array_object;
  Vbo vertex_buffer_object;
} gl_shader_data_t;

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
  Window window;
  gl_vertex_data_s data;
  bool running_state;
  long frame_counter;
  void run();
  void render(const Program &shader_program, const Vao &vao);
  static void cleanup();
};

#endif //OPENGL_DEV_ENGINE_H

