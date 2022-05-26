//
// Created by nami on 5/10/22.
//

#include "../../Include/Game logic/game.h"

static float color_value = 0.0f;
static float translation_value = 0.0f;
Camera Game::camera;  /* NOLINT */

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
  // Load custom mesh.
  Resource_loader object_file("../Resources/Models/cube.obj");
  this->mesh = object_file.load_mesh();

  // Init opengl memory buffers and shaders.
  this->program.create_program();
  this->program.add_shader(GL_VERTEX_SHADER,
                           Resource_loader::load_shader_source("../Resources/Shaders/default.vert").c_str());
  this->program.add_shader(GL_FRAGMENT_SHADER,
                           Resource_loader::load_shader_source("../Resources/Shaders/default.frag").c_str());
  this->program.link();

  // Add shader uniforms to glsl program.
  this->program.add_uniform("fragment_color");
  this->program.add_uniform("transform");
  // Set world view inside window.
  Transform::set_projection(85.0f, (float) Window::get_width(), (float) Window::get_height(),
                            0.1f, 1000.0f);
}

__attribute__((unused)) Transform Game::get_transform() const
{
  return this->transform;
}

__attribute__((unused)) void Game::set_transform(const Transform &transform_)
{
  this->transform = transform_;
}

__attribute__((unused)) Camera Game::get_camera()
{
  return Game::camera;
}

void Game::update()
{
  // Update program uniforms
  auto time = (float) sin(glfwGetTime());
  color_value = std::abs(time);
  translation_value = time / 2;

  Transform::set_camera(Game::camera);  // Update camera position.
  this->transform.set_translation(Vector_3f(translation_value, 0, 5));
  this->transform.set_rotation(Vector_3f(translation_value * 360, translation_value * 360, 0));
//  this->transform.set_scale(Vector_3f(0.7f * translation_value,
//                                      0.7f * translation_value,
//                                      0.7f * translation_value));
}

void Game::render()
{
  this->program.activate(); // Specify what program to use.

  // Set program uniforms.
  this->program.set_uniform("fragment_color", color_value);
  this->program.set_uniform("transform", this->transform.get_projected_transformation());
  this->mesh.draw();
}

void Game::save()
{

}

void Game::set_callbacks()
{
  glfwSetWindowSizeCallback(Window::get_window(), window_viewport_callback);  // Change screen size event.
  glfwSetCursorPosCallback(Window::get_window(), cursor_position_callback);  // Change cursor position event.
  glfwSetCursorEnterCallback(Window::get_window(), cursor_enter_callback);  // Cursor in/out screen event.
  glfwSetMouseButtonCallback(Window::get_window(), mouse_button_callback);  // Mouse button input event.
//  glfwSetScrollCallback(window, scroll_callback);  // Mouse scroll event.
  glfwSetKeyCallback(Window::get_window(), key_callback); // Key input events.
}

/******************************CALLBACKS****************************/

// Whenever the window size changed (by OS or user resize) this callback function executes
void window_viewport_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
  /* make sure the viewport matches the new window dimensions; note that width and
   * height will be significantly larger than specified on retina displays.
   */
  glViewport(0, 0, width, height);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

// Whenever the cursor changes position within the window, this callback function executes.
void cursor_position_callback([[maybe_unused]] GLFWwindow *window, double x_pos, double y_pos)
{
  int window_width = 0, window_height = 0;
  glfwGetWindowSize(window, &window_width, &window_height);
  fflush(stdout);
  if (!glfwWindowShouldClose(window) && (x_pos <= window_width && y_pos <= window_height))
  {
    // For debugging purposes.
    //printf("\nX coordinate : %.2f\nY coordinate : %.2f\n", x_pos, y_pos);
  }
}

// Whenever the mouse cursor enters or leaves the window, this callback function executes.
void cursor_enter_callback([[maybe_unused]] GLFWwindow *window, int entered)
{
  fflush(stdout);
  if (!glfwWindowShouldClose(window) && entered) Logger::alert("Mouse entered\n", INFO);
  else if (!glfwWindowShouldClose(window) && !entered) Logger::alert("Mouse left\n", INFO);
}

// Whenever a mouse button is pressed or released, this callback function executes.
void mouse_button_callback([[maybe_unused]] GLFWwindow *window, int button, int action, int combination)
{
  int window_width = 0, window_height = 0;
  double cursor_x_pos = 0.0f, cursor_y_pos = 0.0f;
  glfwGetWindowSize(window, &window_width, &window_height);
  glfwGetCursorPos(window, &cursor_x_pos, &cursor_y_pos);
  //printf("\nCURSOR IS AT POSITION :\nX = %.2f\nY = %.2f\n", cursor_x_pos, cursor_y_pos);
  if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS && !combination
      && (cursor_x_pos <= window_width && cursor_y_pos <= window_height))
    Logger::alert("USER LEFT CLICKED INSIDE THE WINDOW\n");
  else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE && !combination)
    Logger::alert("USER RELEASED LEFT CLICK INSIDE THE WINDOW\n");
}

void Game::key_callback([[maybe_unused]] GLFWwindow *window, int key, [[maybe_unused]] int scan_code,
                        int action, int combination)
{
  float movement_amount = 0.3f;
  float rotation_amount = 0.3f;

  if (action == GLFW_PRESS || action == GLFW_REPEAT)  // Key pressed or held down.
  {
    switch (key)
    {
      case (GLFW_KEY_F):
        toggle_fullscreen(window);
        break;
      case (GLFW_KEY_ESCAPE):
        glfwSetWindowShouldClose(window, true);
        break;
      case (GLFW_KEY_W):
        Game::camera.move(Game::camera.get_forward(), movement_amount);
        break;
      case (GLFW_KEY_S):
        Game::camera.move(Game::camera.get_forward(), -movement_amount);
        break;
      case (GLFW_KEY_A):
        Game::camera.move(Game::camera.get_left(), movement_amount);
        break;
      case (GLFW_KEY_D):
        Game::camera.move(Game::camera.get_right(), movement_amount);
        break;
      case (GLFW_KEY_UP):
        Game::camera.rotate_x(-rotation_amount);
        break;
      case (GLFW_KEY_DOWN):
        Game::camera.rotate_x(rotation_amount);
        break;
      case (GLFW_KEY_LEFT):
        Game::camera.rotate_y(-rotation_amount);
        break;
      case (GLFW_KEY_RIGHT):
        Game::camera.rotate_y(rotation_amount);
        break;
      default:
        break;
    }
  }
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
