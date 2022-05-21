//
// Created by nami on 5/11/22.
//
#include "../Include/OpenGL Graphics/vertex_test.h"

std::vector<Vertex> set_vertices_data()
{
  const Color vertex_colors(1.0f, 1.0f, 1.0f, 1.0f); // Default color for fragments.

  // Vectors
  const Vector_3f vector_1(-0.25f, -0.5f * float(sqrt(3)) / 3, 0.0);  // Lower left corner.
  const Vector_3f vector_2(0.25f, -0.5f * float(sqrt(3)) / 3, 0.0);  // Lower right corner.
  const Vector_3f vector_3(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0); // Upper corner.
  const Vector_3f vector_4(-0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0); // Inner left.
  const Vector_3f vector_5(0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0); //Inner right.
  const Vector_3f vector_6(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0); // Inner down.

  // Positions (x,y,z)     // Colors (RGB).
  Vertex a(vector_1, vertex_colors);
  Vertex b(vector_2, vertex_colors);
  Vertex c(vector_3, vertex_colors);
  Vertex d(vector_4, vertex_colors);
  Vertex e(vector_5, vertex_colors);
  Vertex f(vector_6, vertex_colors);

  // Create our GLfloat vertices to pass on to the buffers.
  std::vector<Vertex> vertices;
  vertices.push_back(a), vertices.push_back(b), vertices.push_back(c),
      vertices.push_back(d), vertices.push_back(e), vertices.push_back(f);
  return vertices;
}
