//
// Created by nami on 5/11/22.
//

#ifndef OPENGL_DEV_TIME_H
#define OPENGL_DEV_TIME_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include <ctime>

class Time
{
public:
  static const char *get_game_time();
  static const std::time_t get_real_time();
};

#endif //OPENGL_DEV_TIME_H
