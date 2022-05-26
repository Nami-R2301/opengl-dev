//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_SHADER_H
#define GAME_OPENGL_SHADER_H

#include <fstream>
#include <vector>
#include <map>
#include "color.h"
#include "vertex.h"
#include "render.h"
#include "../Logs/logger.h"
#include "../Math/matrix_4f.h"
#include "../../Include/OpenGL Graphics/res_loader.h"

class Shader
{
public:
  Shader();
  [[maybe_unused]] [[nodiscard]] const char *get_fragment_source() const;
  [[maybe_unused]] [[nodiscard]] const char *get_vertex_source() const;
  [[maybe_unused]] void set_fragment_source(const char *file_path);
  [[maybe_unused]] void set_vertex_source(const char *file_path);
  void create_program();
  [[nodiscard]] GLuint get_program() const;
  void add_shader(int shader_type, const char *source) const;
  void delete_shader() const;
  static void source(GLuint count = 1, const char *source = nullptr, int *length = nullptr);
  static void compile(GLuint shader, GLuint shader_type);
  void attach(GLuint shader) const;
  void link() const;
  void validate() const;
  void activate() const;
//  static void scroll_callback([[maybe_unused]] GLFWwindow *window, double x_offset, double y_offset);
  void add_uniform(const char *uniform);
  void set_uniform(const char *uniform_name, int value);
  void set_uniform(const char *uniform_name, float value);
  void set_uniform(const char *uniform_name, const Color &color);
  void set_uniform(const char *uniform_name, const Vector_3f &vector_3f);
  void set_uniform(const char *uniform_name, const Matrix_4f &matrix_4f);
  void cleanup();

private:
  static void compile_errors(unsigned int shader, const char *type);
  GLuint program = 0;
  std::map<const char *, int> uniforms;
  const char *fragment_source = nullptr;
  const char *vertex_source = nullptr;
};

std::string load_shader_source(const char *filename);

#endif //GAME_OPENGL_SHADER_H
