//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_VERTEX_H
#define GAME_OPENGL_VERTEX_H
#include <GLES3/gl3.h>
#include <vector>
#include "color.h"

// Vertex to pass on to our opengl vertex shaders.
class Vertex {
public:
  Vertex();

  Vertex(float x_coord, float y_coord, float z_coord, const Color &);

  Vertex(float x_coord, float y_coord, float z_coord, float red, float green, float blue, float alpha);

  Vertex(const Vertex &);

  void print_vertex() const;

  bool operator==(const Vertex &);

  Vertex &operator=(const Vertex &);

private:
  GLfloat x_pos = 0.0f;
  GLfloat y_pos = 0.0f;
  GLfloat z_pos = 0.0f;
  Color color;
};

#endif //GAME_OPENGL_VERTEX_H
