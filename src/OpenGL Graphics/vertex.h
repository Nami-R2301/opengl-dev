//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_VERTEX_H
#define GAME_OPENGL_VERTEX_H

#include "../Math/vector_3f.h"
#include "color.h"
#include "../Math/vector_2f.h"

#define VERTEX_SIZE sizeof(float) * 9

typedef struct vertex_s
{
  float position[3];
  float color[4];
  float texture_coords[2];
} vertex_t;

#define POSITION_OFFSET offsetof(vertex_t, position)
#define COLOR_OFFSET offsetof(vertex_t, color)
#define TEXTURE_OFFSET offsetof(vertex_t, texture_coords)

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
  bool operator==(const Vertex &);
  Vertex &operator=(const Vertex &);

  void set_texCoord(const Vector_2f &texCoord);

  [[maybe_unused]] const Vector_3f &get_position() const;
  [[maybe_unused]] void set_position(const Vector_3f &position_);
  [[maybe_unused]] const Color &get_color() const;
  [[maybe_unused]] void set_color(const Color &color);
  [[maybe_unused]] const Vector_2f &get_texCoord() const;
private:
  Vector_3f position;
  Color color;
  Vector_2f texCoord;
};

#endif //GAME_OPENGL_VERTEX_H
