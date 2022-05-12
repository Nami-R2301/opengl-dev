//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_ENGINE_H
#define OPENGL_DEV_ENGINE_H

#include "../Include/window.h"
#include "../Include/program.h"
#include "../Include/vao.h"
#include "../Include/vbo.h"
#include "../Include/evo.h"
#include "../Include/constants.h"
#include "../Include/game_time.h"
#include "../Include/game.h"
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
  const double frame_time = 1.0 / FRAME_CAP;
  explicit Engine();
  gl_vertex_data_s get_data();
  void set_data(const gl_vertex_data_s &data);
  void start();
  void stop();
private:
  Game game;
  Window window;
  gl_vertex_data_s data;
  bool running_state;
  unsigned int frames;
  long frame_counter;
  void run();
  void render(Color bg_color, const Program &program, const Vao &vao);
  [[maybe_unused]] static void debug(Vertex *data);
  static void cleanup();
};

static GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle.
        5, 4, 1, // Lower right triangle.
        3, 2, 4 // Upper triangle.
    };

#endif //OPENGL_DEV_ENGINE_H

