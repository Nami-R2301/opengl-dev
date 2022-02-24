//
// Created by nami on 2022-02-23.
//

#ifndef GAME_OPENGL_SHADER_H
#define GAME_OPENGL_SHADER_H
#include <GLES3/gl3.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cerrno>
#include <cassert>

class Shader
{
public:
  explicit Shader(int shader_type);
  ~Shader();
  void source(int count=1, const char* source=nullptr, int* length=nullptr) const;
  void compile();
  [[nodiscard]] GLuint get_value() const;

private:
  void compile_errors(unsigned int shader, const char* type);
  GLuint shader = 0;
  int shader_type = 0;
};

std::string get_file_contents(const char* filename);

#endif //GAME_OPENGL_SHADER_H
