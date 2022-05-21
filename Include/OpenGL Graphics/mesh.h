//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_MESH_H
#define OPENGL_DEV_MESH_H

#include <vector>
#include "vertex.h"
#include "render.h"
#include "../Logs/logger.h"

#define COUNT_VECTOR3D 3
#define COUNT_COLOR 4
#define COLOR_SIZE sizeof(float) * 4
#define VERTEX_SIZE sizeof(float) * 7

class Mesh
{
public:
  Mesh();
  [[nodiscard]] std::vector<GLuint> get_indices() const;
  void set_indices(const std::vector<GLuint> &indices_);
  void bind_evo(const std::vector<GLuint> &indices_) const;
  void add_vertices(const Vertex *vertices, unsigned long size);
  void setup_graphics(const Vertex *vertices, unsigned long size);
  void draw() const;
  void cleanup();
private:
  GLuint vbo = 0;  // Vertex buffer object.
  GLuint vao = 0;  // Vertex array object.
  GLuint evo = 0;  // Element vertex object.
  int size = 0;
  std::vector<GLuint> indices;

  void add_vbo();
  void add_vao();
  void add_evo();
  void bind_vbo() const;
  void bind_vao() const;

  static void unbind_vbo();
  static void unbind_vao();
  static void unbind_evo();
};

#endif //OPENGL_DEV_MESH_H
