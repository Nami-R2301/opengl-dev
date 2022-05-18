//
// Created by nami on 5/11/22.
//

#include "../../Include/Game logic/time.h"

const char *Time::get_game_time()
{
  std::time_t current_time = time(nullptr);
  std::ctime(&current_time);
  return std::ctime(&current_time);;
}

const std::time_t Time::get_real_time()
{
  auto current_time = time(nullptr);
  return current_time;
}
