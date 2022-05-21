//
// Created by nami on 5/11/22.
//

#ifndef OPENGL_DEV_TIME_H
#define OPENGL_DEV_TIME_H

// GLFW
#include <GLFW/glfw3.h>

// std and chrono.
#include <iostream>
#include <chrono>

class Time
{
public:
  static const char *get_game_time();
  static const std::time_t get_real_time();
};

#endif //OPENGL_DEV_TIME_H
