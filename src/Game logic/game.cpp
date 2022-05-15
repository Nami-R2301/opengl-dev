//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

Game::Game()
{
  std::vector<Vertex> data = {Vertex(Vector_3f(1, -1, 0), Color(1, 1, 1)),
                              Vertex(Vector_3f(-1, 1, 0), Color(1, 1, 1)),
                              Vertex(Vector_3f(0, 1, 0), Color(1, 1, 1))};
  this->mesh.add_vertices(data);
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
