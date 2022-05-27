//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_VERTEX_H
#define GAME_OPENGL_VERTEX_H

#include "../Math/vector_3f.h"
#include "color.h"
#include "../Math/vector_2f.h"

// Manipulation of vertices to pass on to our opengl vertex_source shaders.
class Vertex
{
public:
  Vertex();
  Vertex(float x_coord, float y_coord, float z_coord, float red, float green, float blue, float alpha);
  Vertex(const Vector_2f &position, const Color &color);
  Vertex(const Vector_3f &position, const Color &);
  Vertex(const Vector_3f &position, const Vector_2f &tex_coord);
  Vertex(const Vertex &);

  [[nodiscard]] float length() const;
  void print_vertex() const;

  [[maybe_unused]] [[nodiscard]] const Vector_3f &get_position() const;
  [[maybe_unused]] void set_position(const Vector_3f &position_);
  [[maybe_unused]] [[nodiscard]] const Color &get_color() const;
  [[maybe_unused]] void set_color(const Color &color);
  const Vector_2f &get_texCoord() const;
  void set_texCoord(const Vector_2f &texCoord);

  bool operator==(const Vertex &);
  Vertex &operator=(const Vertex &);
private:
  Vector_3f position;
  Color color;
  Vector_2f texCoord;
};

#endif //GAME_OPENGL_VERTEX_H
