//
// Created by nami on 5/10/22.
//

#ifndef OPENGL_DEV_GAME_H
#define OPENGL_DEV_GAME_H

#include "../OpenGL Graphics/mesh.h"
#include "../../Include/OpenGL Graphics/vertex_test.h"

class Game
{
public:
  Game();
  void init(const Vertex *vertices, unsigned long size);
  void input();
  void update();
  void render();
  void save();
  void cleanup();
  [[nodiscard]] Mesh get_mesh() const;
  void set_mesh(const Mesh &mesh);
private:
  Mesh mesh;
};

#endif //OPENGL_DEV_GAME_H
