//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_MESH_H
#define OPENGL_DEV_MESH_H

#include <vector>
#include "vertex.h"
#include "render.h"
#include "../Logs/logger.h"

#define COUNT_VECTOR2D 2
#define COUNT_VECTOR3D 3
#define COUNT_COLOR 4
//#define COLOR_SIZE sizeof(float) * 4
#define VERTEX_SIZE sizeof(float) * 9
//#define TEXTURE_SIZE VECTOR2F_SIZE

#define POSITION_OFFSET 0
#define COLOR_OFFSET sizeof(float) * 3
#define TEXTURE_OFFSET sizeof(float) * 7

class Mesh
{
public:
  Mesh();
  [[nodiscard]] std::vector<GLuint> get_indices() const;
  void set_indices(const std::vector<GLuint> &indices_);
  void bind_evo(const std::vector<GLuint> &indices_) const;
  void add_vertices(const Vertex *vertices, unsigned long size);
  void set_tex_id(unsigned int tex_id_);
  void setup_graphics(const Vertex *vertices, unsigned long size);
  void draw() const;
  void cleanup();
private:
  GLuint vbo = 0;  // Vertex buffer object.
  GLuint vao = 0;  // Vertex array object.
  GLuint evo = 0;  // Element vertex object.
  GLuint tex = 0;  // Texture index.
  int size = 0;
  std::vector<GLuint> indices;

  void add_vbo();
  void add_vao();
  void add_evo();

  void bind_vbo() const;
  void bind_vao() const;
  void bind_tex(unsigned int slot = 0) const;

  static void unbind_vbo();
  static void unbind_vao();
  static void unbind_evo();
  static void unbind_tex();
};

#endif //OPENGL_DEV_MESH_H
