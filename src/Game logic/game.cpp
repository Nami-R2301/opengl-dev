//
// Created by nami on 5/10/22.
//

#include "game.h"
#include "../OpenGL Graphics/window.h"
#include "../OpenGL Graphics/res_loader.h"
#include "input.h"

static float translation_value = 0.0f;

Game::Game()
{
  Game::set_callbacks();  // Set our mouse and keyboard callbacks.
  this->material = Material(load_texture_file("../Resources/Textures/tiles.png"),
                            Color(1.0f, 1.0f, 1.0f, 1.0f));
  // Init opengl memory buffers and shaders.
  this->program.setup_basic_shader();

  // Add shader uniforms to glsl program.
  this->program.add_uniform("uniform_color");
  this->program.add_uniform("transform");
  prepare_mesh();  // Initialize and load meshes to draw on screen.
}

void Game::set_callbacks()
{
  glfwSetFramebufferSizeCallback(Window::get_window(), window_viewport_callback);  // When resizing window.
  glfwSetKeyCallback(Window::get_window(), window_key_callback);  // When changing resolution.
}

void Game::prepare_mesh()
{
  // Load custom mesh.
  res_loader_t custom_mesh = load_mesh("Models/cube.obj");  // Load obj file containing custom object mesh.
  // Setup vao layout.
  Buffer_layout layout;
  layout.push<Vector_3f>(1), layout.push<Color>(1), layout.push<Vector_2f>(1);

  this->mesh.setup_mesh(custom_mesh.vertices, custom_mesh.indices, layout);
  Shader::deactivate();  // Unbind program for now until we draw.

  // Set world view inside window.
  this->transform.set_projection(125.0f, (float) Window::get_width(), (float) Window::get_height(),
                                 0.1f, 1000.0f);
}

void Game::input()
{
  this->camera.input();  // Move around the camera based on input.
  Input::reset();  // Reset all the mouse and key states for this frame to avoid duplication of actions.
}

void Game::update()
{
  auto time = (float) sin(glfwGetTime());
  translation_value = time / 2;

  // Update model matrix transformations.
  this->transform.set_translation(Vector_3f(translation_value, 0, 5));
  this->transform.set_rotation(Vector_3f(translation_value * 360, translation_value * 360, 0));
//  this->transform.set_scale(Vector_3f(0.7f * translation_value,
//                                      0.7f * translation_value,
//                                      0.7f * translation_value));
  // Update shader program.
  this->program.activate(); // Activate program for next draw.
  this->program.set_uniform("transform", this->transform.get_projected_transformation(get_camera()));
  this->program.set_uniform("uniform_color", material.get_color());
}

void Game::render()
{
  this->mesh.draw();  // GPU draws everything.
}

void Game::save()
{

}

void Game::cleanup()
{
  save();
  get_mesh().delete_buffers();
  get_program().cleanup();
}

/******************************CALLBACKS****************************/

// Whenever the window size changed (by OS or user resize) this callback function executes
void Game::window_viewport_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
  /* Make sure the viewport matches the new window dimensions; note that width and
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

Mesh Game::get_mesh() const
{
  return mesh;
}

Shader Game::get_program() const
{
  return this->program;
}

Camera Game::get_camera() const
{
  return this->camera;
}

[[maybe_unused]] void Game::set_mesh(const Mesh &mesh_)
{
  Game::mesh = mesh_;
}

[[maybe_unused]] Transform Game::get_transform() const
{
  return this->transform;
}

[[maybe_unused]] void Game::set_transform(const Transform &transform_)
{
  this->transform = transform_;
}

void *Game::operator new(unsigned long size)
{
  auto game = (Game *) malloc(size);
  if (game == nullptr)
  {
    alert(ERROR, "NOT ENOUGH MEMORY ON THE HEAP");
    exit(ERROR_HEAP_ALLOC);
  }
  return game;
}

void Game::operator delete(void *game)
{
  if (game != nullptr) free(game);
}
