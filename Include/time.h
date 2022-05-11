//
// Created by nami on 5/11/22.
//

#ifndef OPENGL_DEV_TIME_H
#define OPENGL_DEV_TIME_H

#include <ctime>

class time
{
public:
  static long get_time();
  static double get_delta();
  static void set_delta();
private:
  static double delta;
};

#endif //OPENGL_DEV_TIME_H
