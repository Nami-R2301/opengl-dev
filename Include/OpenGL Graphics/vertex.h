//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_VERTEX_H
#define GAME_OPENGL_VERTEX_H

#include <GLES3/gl3.h>
#include <vector>
#include "../Math/vector_3f.h"
#include "color.h"
#include <cmath>

#define VERTEX_SIZE 7  // Position (3) + color (4).

// Vertex to pass on to our opengl vertex shaders.
class Vertex
{
public:
  Vertex();
  Vertex(const Vector_3f &vector_3f, const Color &);
  Vertex(float x_coord, float y_coord, float z_coord, float red, float green, float blue, float alpha);
  Vertex(const Vertex &);
  [[nodiscard]] float length() const;
  void print_vertex() const;
  bool operator==(const Vertex &);
  Vertex &operator=(const Vertex &);
  [[nodiscard]] const Vector_3f &get_position() const;
  void set_position(const Vector_3f &position_);
  [[nodiscard]] const Color &get_color() const;
  void set_color(const Color &color);

private:
  Vector_3f position;
  Color color;
};

#endif //GAME_OPENGL_VERTEX_H
