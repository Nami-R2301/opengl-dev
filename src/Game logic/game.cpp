//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

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
  this->program.add_shader(GL_VERTEX_SHADER,
                           get_file_contents("../Resources/Shaders/default.vert").c_str());
  this->program.add_shader(GL_FRAGMENT_SHADER,
                           get_file_contents("../Resources/Shaders/default.frag").c_str());
  this->program.link();

  Resource_loader object_file = Resource_loader("../../Resources/Models/default.obj");
//  const std::vector<Vertex> vertices = object_file.load_vertices();
//  const std::vector<GLuint> evo_indices = object_file.load_faces();

  // Get all relevant data for vertices and fragments.
  std::vector<Vertex> vertices = set_vertices_data();
  // Setting up evo.
  std::vector<GLuint> evo_indices =
      {
          0, 3, 5, // Lower left triangle.
          3, 2, 4, // Upper triangle.
          5, 4, 1 // Lower right triangle.
      };
  this->mesh.set_indices(evo_indices);
  this->mesh.setup_graphics(vertices.data(), VERTEX_SIZE * vertices.size());

  // Add shader uniforms.
  this->program.add_uniform("fragment_color");
  this->program.add_uniform("transform");
}

[[maybe_unused]] Transform Game::get_transform() const
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
  auto time = (float) sin(glfwGetTime());
  color_value = std::abs(time);
  translation_value = time / 2;
  this->transform.set_translation(Vector_3f(translation_value, translation_value, 0));
  this->transform.set_rotation(Vector_3f(translation_value * 360, 0, 0));
  this->transform.set_scale(Vector_3f(translation_value * 2, translation_value * 2, translation_value * 2));
}

void Game::render()
{
  this->program.activate(); // Specify what program to use.
  // Set program uniforms.
  this->program.set_uniform("fragment_color", color_value);
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
