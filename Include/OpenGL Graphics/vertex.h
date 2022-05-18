//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_VERTEX_H
#define GAME_OPENGL_VERTEX_H

#include "../Math/vector_3f.h"
#include "color.h"
#include "../Math/vector_2f.h"

#define VERTEX_SIZE 7  // Position (3) + color (4).

// Manipulation of vertices to pass on to our opengl vertex_source shaders.
class Vertex
{
public:
  Vertex();
  Vertex(float x_coord, float y_coord, float z_coord, float red, float green, float blue, float alpha);
  Vertex(const Vector_2f &vector_2f, const Color &color);
  Vertex(const Vector_3f &vector_3f, const Color &);
  Vertex(const Vertex &);
  [[nodiscard]] float length() const;
  void print_vertex() const;
  bool operator==(const Vertex &);
  Vertex &operator=(const Vertex &);
  [[maybe_unused]] [[nodiscard]] const Vector_3f &get_position() const;
  [[maybe_unused]] void set_position(const Vector_3f &position_);
  [[maybe_unused]] [[nodiscard]] const Color &get_color() const;
  [[maybe_unused]] void set_color(const Color &color);
private:
  Vector_3f position;
  Color color;
};

#endif //GAME_OPENGL_VERTEX_H
