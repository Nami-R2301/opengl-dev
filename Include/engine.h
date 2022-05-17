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
  ~Engine();
  [[nodiscard]] bool get_running_state() const;
  gl_vertex_data_s get_data();
  void set_shader_data(const gl_vertex_data_s &data);
  void start();
  void stop(const Shader &shader_program);
  [[maybe_unused]] static void debug(Vertex *data);
  [[maybe_unused]] [[nodiscard]] const Window &get_window() const;
  [[maybe_unused]] void set_window(const Window &window);
private:
  Game game;
  Window window;
  gl_vertex_data_s data;
  bool running_state;
  long frame_counter;
  void run();
  void render(const Shader &program, Color &color);
  void cleanup(const Shader &shader_program = Shader());
};

#endif //OPENGL_DEV_ENGINE_H

