//
// Created by nami on 5/10/22.
//

#ifndef OPENGL_DEV_GAME_H
#define OPENGL_DEV_GAME_H

#include "../OpenGL Graphics/mesh.h"
#include "../OpenGL Graphics/vertex_test.h"
#include "../OpenGL Graphics/shader.h"

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
private:
  Mesh mesh;
  Shader program;
};

#endif //OPENGL_DEV_GAME_H
