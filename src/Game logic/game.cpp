//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

Game::Game() = default;

void Game::init()
{
  std::vector<Vertex> data = {Vertex(Vector_3f(0, 3, 5), Color(1, 1, 1)),
                              Vertex(Vector_3f(5, 4, 1), Color(1, 1, 1)),
                              Vertex(Vector_3f(3, 2, 4), Color(1, 1, 1))};
  this->mesh.setup_graphics(data);
}

const Mesh &Game::get_mesh() const
{
  return mesh;
}

void Game::set_mesh(const Mesh &mesh_)
{
  Game::mesh = mesh_;
}

void Game::input()
{

}

void Game::render()
{
  this->mesh.draw();
}

void Game::update()
{

}

void Game::save()
{

}
