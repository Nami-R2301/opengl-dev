//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

static float scale_value = 0.0f;
static float color_value = 0.0f;
static float translation_value = 0.0f;

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
  this->program.create_program();
  // Get all relevant data for vertices and fragments.
  std::vector<Vertex> vertices = set_vertices_data();
  this->program.add_shader(GL_VERTEX_SHADER,
                           get_file_contents("../Resources/Shaders/default.vert").c_str());
  this->program.add_shader(GL_FRAGMENT_SHADER,
                           get_file_contents("../Resources/Shaders/default.frag").c_str());
  this->program.link();
  this->mesh.setup_graphics(vertices.data(), sizeof(Vertex) * vertices.size());

  // Add shader uniforms.
  this->program.add_uniform("fragment_color");
  this->program.add_uniform("transform");
  this->program.add_uniform("scale");
}

Transform Game::get_transform() const
{
  return this->transform;
}

[[maybe_unused]] void Game::set_transform(const Transform &transform_)
{
  this->transform = transform_;
}

void Game::input()
{

}

void Game::update()
{
  // Update program uniforms
  scale_value = 0.15f;
  auto time = (float) sin(glfwGetTime());
  color_value = std::abs(time);
  translation_value = time;
  this->transform.set_translation(translation_value, 0, 0);
}

void Game::render()
{
  this->program.activate(); // Specify what program to use.
  // Set program uniforms.
  this->program.set_uniform("fragment_color", color_value);
  this->program.set_uniform("scale", scale_value);
  this->program.set_uniform("transform", this->transform.get_transformation());
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
