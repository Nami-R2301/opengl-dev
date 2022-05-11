//
// Created by nami on 5/11/22.
//
#include "../Include/vertex_test.h"

std::vector<Vertex> set_vertices_data()
{
  const Color vertex_colors(0.25f, 0.84f, 0.5f, 1.0f); // Default color for fragments.

  // Coordinates (x,y,z)                                          // Colors (RGB).
  Vertex a(-0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower left corner.
  Vertex b(0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower right corner.
  Vertex c(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, vertex_colors); // Upper corner.
  Vertex d(-0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner left.
  Vertex e(0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); //Inner right.
  Vertex f(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner down.

  // Create our GLfloat vertices to pass on to the buffers.
  std::vector<Vertex> vertices;
  vertices.push_back(a), vertices.push_back(b), vertices.push_back(c),
      vertices.push_back(d), vertices.push_back(e), vertices.push_back(f);
  return vertices;
}
