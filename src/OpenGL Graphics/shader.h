//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_SHADER_H
#define GAME_OPENGL_SHADER_H

#include <unordered_map>
#include "color.h"
#include "vertex.h"
#include "../Math/matrix_4f.h"

class Shader
{
public:
  Shader();
  Shader(const char *vertex_file_path, const char *fragment_file_path);

  [[nodiscard]] unsigned int get_program() const;

  // Initial setup.
  void create_program();

  // Shader creating and buffer assignment.
  void add_shader(int shader_type, const char *source) const;
  void delete_shader() const;
  static void source(unsigned int count = 1, const char *source = nullptr, int *length = nullptr);
  static void compile(unsigned int shader, unsigned int shader_type);
  void attach(unsigned int shader) const;
  void link() const;
  void validate() const;
  static void deactivate();
  void activate() const;

  // Uniform handling.
  [[nodiscard]] int get_uniform_location(const char *uniform);
  void add_uniform(const char *uniform);
  void set_uniform(const char *uniform_name, const Color &color);
  void set_uniform(const char *uniform_name, const Matrix_4f &matrix_4f);

  [[maybe_unused]] void set_uniform(const char *uniform_name, int value);
  [[maybe_unused]] void set_uniform(const char *uniform_name, float value);
  [[maybe_unused]] void set_uniform(const char *uniform_name, const Vector_3f &vector_3f);

  void cleanup();

private:
  unsigned int m_renderer_id = 0;
  std::unordered_map<const char *, int> uniforms;

  static void compile_errors(unsigned int shader, const char *type);
};

#endif //GAME_OPENGL_SHADER_H
