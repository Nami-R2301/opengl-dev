//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_SHADER_H
#define GAME_OPENGL_SHADER_H

#include <GLES3/gl3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "color.h"

class Shader
{
public:
  Shader();
  [[nodiscard]] GLuint get_program() const;
  static std::string get_shader_source(const char *shader_path);
  [[nodiscard]] std::vector<GLuint> get_shaders() const;
  void add_shader(int shader_type, const char *source) const;
  void delete_shaders() const;
  static void source(GLuint count = 1, const char *source = nullptr, int *length = nullptr);
  static void compile(GLuint shader, GLuint shader_type);
  void attach(GLuint shader) const;
  void link() const;
  void validate() const;
  void activate() const;
  void update_scale(float scale) const;
  void update_color(const Color &color) const;

private:
  static void compile_errors(unsigned int shader, const char *type);
  GLuint program = 0;
  std::vector<GLuint> shaders;
};

std::string get_file_contents(const char* filename);

#endif //GAME_OPENGL_SHADER_H
