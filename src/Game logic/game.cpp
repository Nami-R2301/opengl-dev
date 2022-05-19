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
  this->mesh = Mesh();
  this->program = Shader();
  this->program.create_program();
  // Get all relevant data for vertices and fragments.
  std::vector<Vertex> vertices = set_vertices_data();
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
  this->program.activate(); // Specify what program to use.

  // Update fragment_source uniform
  this->program.update_color((float) (sin(glfwGetTime()) + .6),
                             (float) (sin(glfwGetTime()) + .1),
                             (float) (sin(glfwGetTime()) + .3), 1.0f);  // Update object color.
  this->program.update_scale(0.20f);
}

void Game::update()
{
  input();
  render();
}

void Game::draw()
{
  this->mesh.draw();
}

void Game::save()
{

}

void Game::cleanup()
{
  save();
  get_mesh().cleanup();
  get_program().delete_shader();
}

void *Game::operator new(unsigned long size)
{
  auto game = (Game *) malloc(size);
  if (game == nullptr)
  {
    Logger::alert("NOT ENOUGH MEMORY ON THE HEAP\n", ERROR);
    exit(ERROR_HEAP_ALLOC);
  }
  return game;
}

void Game::operator delete(void *game)
{
  if (game != nullptr) free(game);
}
