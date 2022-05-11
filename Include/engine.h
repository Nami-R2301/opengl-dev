//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_ENGINE_H
#define OPENGL_DEV_ENGINE_H
#define MAX_FPS 1000000000L

#include "../Include/window.h"
#include "../Include/program.h"
#include "../Include/vao.h"
#include "../Include/vbo.h"
#include "../Include/evo.h"
#include "../Include/constants.h"
#include "../Include/time.h"
#include <cmath>

typedef struct gl_data_s
{
  const char *vertex_source = nullptr;
  const char *fragment_source = nullptr;
  std::vector<Vertex> vertices;
} gl_data_t;

class Engine
{
public:
  explicit Engine();
  gl_data_t get_data();
  void set_data(const gl_data_t &data);
  void start();
  void stop();
private:
  Window window;
  gl_data_t data;
  bool running_state;
  clock_t delta_time = 0;
  unsigned int frames = 0;
  double framerate = 60;
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

