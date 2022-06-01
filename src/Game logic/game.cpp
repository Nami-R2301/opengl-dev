//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

static float translation_value = 0.0f;

Game::Game()
{
  Game::set_callbacks();  // Set our mouse and keyboard callbacks.
  this->material = Material(Resource_loader::load_texture_file("../Resources/Textures/tiles.png"),
                            Color(1.0f, 1.0f, 1.0f, 1.0f));
  // Init opengl memory buffers and shaders.
  this->program.setup_basic_shader();

  // Add shader uniforms to glsl program.
  this->program.add_uniform("uniform_color");
  this->program.add_uniform("transform");
  prepare_mesh();  // Initialize and load meshes to draw on screen.
}

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
  // Load custom mesh.
  Resource_loader object_file("Models/cube.obj");
  object_file.load_mesh();  // Load obj file containing custom object mesh.

  this->mesh.set_tex_id(this->material.get_texture().get_id());
  this->mesh.set_indices(object_file.get_indices());
  this->mesh.setup_graphics(object_file.get_vertices().data(),
                            VERTEX_SIZE * object_file.get_vertices().size());

  // Set world view inside window.
  this->transform.set_projection(125.0f, (float) Window::get_width(), (float) Window::get_height(),
                                 0.1f, 1000.0f);
}

[[maybe_unused]] Transform Game::get_transform() const
{
  return this->transform;
}

[[maybe_unused]] void Game::set_transform(const Transform &transform_)
{
  this->transform = transform_;
}

Camera Game::get_camera()
{
  return this->camera;
}

void Game::input()
{
  this->camera.input();
  Input::reset();  // Reset all the mouse and key states for this frame to avoid duplication of actions.
}

void Game::update()
{
  auto time = (float) sin(glfwGetTime());
  translation_value = time / 2;

  this->transform.set_translation(Vector_3f(translation_value, 0, 5));
  this->transform.set_rotation(Vector_3f(translation_value * 360, translation_value * 360, 0));
//  this->transform.set_scale(Vector_3f(0.7f * translation_value,
//                                      0.7f * translation_value,
//                                      0.7f * translation_value));
}

void Game::render()
{
  this->program.activate(); // Specify what program to use.
  this->program.set_uniform("transform", this->transform.get_projected_transformation(get_camera()));
  this->program.set_uniform("uniform_color", material.get_color());
  this->mesh.draw();
}

void Game::save()
{

}

void Game::set_callbacks()
{
  glfwSetFramebufferSizeCallback(Window::get_window(), window_viewport_callback);
  glfwSetKeyCallback(Window::get_window(), window_key_callback);
}

/******************************CALLBACKS****************************/

// Whenever the window size changed (by OS or user resize) this callback function executes
void Game::window_viewport_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
  /* make sure the viewport matches the new window dimensions; note that width and
   * height will be significantly larger than specified on retina displays.
   */
  glViewport(0, 0, width, height);
}

void Game::window_key_callback([[maybe_unused]] GLFWwindow *window, [[maybe_unused]]  int key,
                               [[maybe_unused]] int scancode, [[maybe_unused]] int action,
                               [[maybe_unused]] int mods)
{
  Window::input();
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
    Logger::alert(ERROR, "NOT ENOUGH MEMORY ON THE HEAP");
    exit(ERROR_HEAP_ALLOC);
  }
  return game;
}

void Game::operator delete(void *game)
{
  if (game != nullptr) free(game);
}
