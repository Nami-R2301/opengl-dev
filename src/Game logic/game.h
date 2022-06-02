//
// Created by nami on 5/10/22.
//

#ifndef OPENGL_DEV_GAME_H
#define OPENGL_DEV_GAME_H

#include "../OpenGL Graphics/mesh.h"
#include "../OpenGL Graphics/shader.h"
#include "../OpenGL Graphics/material.h"
#include "../Math/transform.h"

class Game
{
public:
  explicit Game();

  static void set_callbacks();
  static void window_viewport_callback([[maybe_unused]] GLFWwindow *window, int width, int height);
  static void window_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

  void prepare_mesh();
  void input();
  void update();
  void render();
  void save();
  void cleanup();

  [[nodiscard]] Shader get_program() const;
  [[nodiscard]] Mesh get_mesh() const;
  [[nodiscard]] Camera get_camera() const;
  [[maybe_unused]] Transform get_transform() const;

  [[maybe_unused]] void set_mesh(const Mesh &mesh);
  [[maybe_unused]] void set_transform(const Transform &transform_);

  void *operator new(unsigned long size);
  void operator delete(void *game);
private:
  Mesh mesh;
  Shader program;
  Transform transform;
  Material material;
  Camera camera;
};

#endif //OPENGL_DEV_GAME_H
