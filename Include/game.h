//
// Created by nami on 5/10/22.
//

#ifndef OPENGL_DEV_GAME_H
#define OPENGL_DEV_GAME_H

#include "program.h"
#include "vao.h"

class Game
{
public:
  Game();
  void input();
  void run();
  void update();
  void save();
};

#endif //OPENGL_DEV_GAME_H
