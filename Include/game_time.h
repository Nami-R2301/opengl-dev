//
// Created by nami on 5/11/22.
//

#ifndef OPENGL_DEV_GAME_TIME_H
#define OPENGL_DEV_GAME_TIME_H

#include <iostream>
#include <chrono>
#include <ctime>

class Time
{
public:
  const static long second = 1000000000L;
  static long get_time_nanoseconds();
  static double get_delta();
  static void set_delta();
private:
  static double delta;
};

#endif //OPENGL_DEV_GAME_TIME_H
