//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_CONSTANTS_H
#define OPENGL_DEV_CONSTANTS_H
#include "../Include/color.h"
#include "../Include/vertex.h"
#include <cmath>
#include "../Include/shader.h"

Color vertex_colors(1.0f, 0.84f, 0.00f, 1.0); // Default color for fragments.

// Create our GLfloat vertices to pass on to the buffers.
Vertex a(-0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower left corner.
Vertex b(0.25f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Lower right corner.
Vertex c(0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, vertex_colors); // Upper corner.
Vertex d(-0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner left.
Vertex e(0.25f / 2, 0.25f * float(sqrt(3)) / 3, 0.0f, vertex_colors); //Inner right.
Vertex f(0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, vertex_colors); // Inner down.
Vertex vertices[] = {a, b, c, d, e, f};

GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle.
        5, 4, 1, // Lower right triangle.
        3, 2, 4 // Upper triangle.
    };

std::string vertex_source = get_file_contents("../Resources/Shaders/default.vert");
std::string fragment_source = get_file_contents("../Resources/Shaders/default.frag");


#endif //OPENGL_DEV_CONSTANTS_H
