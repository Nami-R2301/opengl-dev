//
// Created by nami on 5/11/22.
//

#include "../../Include/Game logic/time.h"
using namespace std::chrono;

long Time::get_game_time()
{
  return (long) glfwGetTime();
}

const char *Time::get_real_time()
{
  std::time_t current_time = time(nullptr);
  std::ctime(&current_time);
  return std::ctime(&current_time);
}
