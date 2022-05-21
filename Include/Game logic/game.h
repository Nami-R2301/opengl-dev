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
  void *operator new(unsigned long size);
  void operator delete(void *game);
  [[maybe_unused]] [[nodiscard]] Transform get_transform() const;
  [[maybe_unused]] void set_transform(const Transform &transform_);
private:
  Mesh mesh;
  Shader program;
  Transform transform;
};

#endif //OPENGL_DEV_GAME_H
