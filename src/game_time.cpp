//
// Created by nami on 5/11/22.
//

#include "../Include/game_time.h"

long Time::get_time_nanoseconds()
{
  auto nanoseconds =
      std::chrono::duration_cast<std::chrono::nanoseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch());
  return nanoseconds.count();
}
