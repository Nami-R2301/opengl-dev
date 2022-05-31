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
#include "../OpenGL Graphics/material.h"

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
  void prepare_mesh();
  void input();
  void update();
  void render();
  void save();
  void cleanup();

  [[nodiscard]] Shader get_program();
  [[nodiscard]] Mesh get_mesh() const;
  [[maybe_unused]] void set_mesh(const Mesh &mesh);
  [[maybe_unused]] Transform get_transform() const;
  [[maybe_unused]] void set_transform(const Transform &transform_);
  [[nodiscard]] Camera get_camera();

  void *operator new(unsigned long size);
  void operator delete(void *game);

  static void set_callbacks();
  static void window_viewport_callback([[maybe_unused]] GLFWwindow *window, int width, int height);
  static void window_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
private:
  Mesh mesh;
  Shader program;
  Transform transform;
  Material material;
  Camera camera;
};

//void scroll_callback([[maybe_unused]] GLFWwindow *, double, double);

#endif //OPENGL_DEV_GAME_H
