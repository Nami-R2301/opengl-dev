//
// Created by nami on 5/31/22.
//
#include "../Include/engine.h"

int main()
{
  // Setup and start the engine.
  auto *game_engine = new Engine();
  game_engine->run();  // Run game.
  delete game_engine;  // Cleanup procedure and deallocate all resources from heap.
  return 0;
}