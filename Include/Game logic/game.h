//
// Created by nami on 5/10/22.
//

#ifndef OPENGL_DEV_GAME_H
#define OPENGL_DEV_GAME_H

#include "../OpenGL Graphics/mesh.h"
#include "../OpenGL Graphics/res_loader.h"
#include "../OpenGL Graphics/vertex_test.h"
#include "../OpenGL Graphics/shader.h"
#include "../Math/transform.h"
#include "../OpenGL Graphics/window.h"

typedef struct gl_data_s
{
  const char *vertex_source = nullptr;
  const char *fragment_source = nullptr;
  std::vector<Vertex> vertices;
} gl_vertex_data_s;

class Game
{
public:
  Game();

  [[nodiscard]] Shader get_program();
  void prepare_mesh();
  void input();
  void update();
  void render();
  void save();
  void cleanup();

  [[nodiscard]] Mesh get_mesh() const;
  [[maybe_unused]] void set_mesh(const Mesh &mesh);
  __attribute__((unused)) Transform get_transform() const;
  __attribute__((unused)) void set_transform(const Transform &transform_);
  [[nodiscard]] static Camera get_camera();

  void *operator new(unsigned long size);
  void operator delete(void *game);

  static void set_callbacks();
private:
  Mesh mesh;
  Shader program;
  Transform transform;
  static Camera camera;
};

void toggle_fullscreen(GLFWwindow *window);

void window_viewport_callback([[maybe_unused]] GLFWwindow *, int, int);

void cursor_position_callback(GLFWwindow *window, double, double);

void cursor_enter_callback([[maybe_unused]] GLFWwindow *, int);

void mouse_button_callback([[maybe_unused]] GLFWwindow *, int, int, int);

void scroll_callback([[maybe_unused]] GLFWwindow *, double, double);

void key_callback([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scan_code,
                  int action, int combination);

#endif //OPENGL_DEV_GAME_H
