//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

Game::Game() = default;

void Game::init(const Vertex *vertices, unsigned long size)
{
  this->mesh.setup_graphics(vertices, size);
}

Mesh Game::get_mesh() const
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

void Game::cleanup()
{
}
