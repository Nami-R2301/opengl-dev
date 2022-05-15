//
// Created by nami on 5/14/22.
//

#ifndef OPENGL_DEV_MESH_H
#define OPENGL_DEV_MESH_H

#include "vertex.h"
#include "vbo.h"
#include "vao.h"
#include "evo.h"

static GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle.
        5, 4, 1, // Lower right triangle.
        3, 2, 4 // Upper triangle.
    };

class Mesh
{
public:
  Mesh();
  void add_vbo();
  void add_vao();
  void add_evo();
  void bind_vbo() const;
  void bind_vao() const;
  void bind_evo() const;
  void add_vertices(const std::vector<Vertex> &data);
  void setup_graphics(const std::vector<Vertex> &data);
  void draw() const;
private:
  GLuint vbo = 0;
  GLuint vao = 0;
  GLuint evo = 0;
  int size = 0;
  static void unbind_vbo();
  static void unbind_vao();
  static void unbind_evo();
};

#endif //OPENGL_DEV_MESH_H
