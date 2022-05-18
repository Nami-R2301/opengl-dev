//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

Game::Game() = default;

Mesh Game::get_mesh() const
{
  return mesh;
}

[[maybe_unused]] void Game::set_mesh(const Mesh &mesh_)
{
  Game::mesh = mesh_;
}

Shader Game::get_program()
{
  return this->program;
}

void Game::prepare_mesh()
{
  // Get all relevant data for vertices and fragments.
  std::vector<Vertex> vertices = set_vertices_data();
  this->program.create_program();
  this->program.add_shader(GL_VERTEX_SHADER,
                           get_file_contents("../Resources/Shaders/default.vert").c_str());
  this->program.add_shader(GL_FRAGMENT_SHADER,
                           get_file_contents("../Resources/Shaders/default.frag").c_str());
  this->program.link();
  this->mesh.setup_graphics(vertices.data(), sizeof(Vertex) * vertices.size());
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
