//
// Created by nami on 5/11/22.
//

#ifndef OPENGL_DEV_TIME_H
#define OPENGL_DEV_TIME_H

#include <GLFW/glfw3.h>
#include <ctime>

class Time
{
public:
  static double get_game_time();
  static const char *get_real_time();
};

#endif //OPENGL_DEV_TIME_H
