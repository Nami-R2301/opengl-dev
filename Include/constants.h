//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_CONSTANTS_H
#define OPENGL_DEV_CONSTANTS_H
#include "../Include/color.h"
#include "../Include/vertex.h"
#include <cmath>
#include "../Include/shader.h"

GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle.
        5, 4, 1, // Lower right triangle.
        3, 2, 4 // Upper triangle.
    };

std::string vertex_source = get_file_contents("../Resources/Shaders/default.vert");
std::string fragment_source = get_file_contents("../Resources/Shaders/default.frag");


#endif //OPENGL_DEV_CONSTANTS_H
