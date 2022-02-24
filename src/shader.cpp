//
// Created by nami on 2022-02-23.
//
#include <cstring>
#include "../Include/shader.h"

// Create shader based on type.
Shader::Shader(int type)
{
  assert(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);
  shader_type = type;
  shader = glCreateShader(type);
}

// Delete the shaders since they have been compiled and linked in the program.
Shader::~Shader()
{
  glDeleteShader(shader);
}

//Set the source code in shader to the source code in the array of strings specified by string.
void Shader::source(int count, const char* source, int* length) const
{
  glShaderSource(shader_type, count, &source, length);
}

// Compile the shaders into machine code to pass on to the GPU.
void Shader::compile()
{
  glCompileShader(shader);
  if(shader_type == GL_VERTEX_SHADER)
  {
    // Checks if Shader compiled successfully
    compile_errors(shader, "VERTEX");
  }
  else
  {
    // Checks if Shader compiled successfully
    compile_errors(shader, "FRAGMENT");
  }
}

GLuint Shader::get_value() const
{
  return shader;
}

std::string get_file_contents(const char *filename)
{
  std::ifstream in((filename), std::ios::binary);
  if(in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], (long) contents.size());
    in.close();
    return contents;
  }
  throw errno;
}

// Checks if the different Shaders have compiled properly
void Shader::compile_errors(unsigned int _shader_, const char* type)
{
  // Stores status of compilation
  GLint hasCompiled;
  // Character array to store error message in
  char infoLog[1024];
  if (strcmp(type, "PROGRAM") != 0)
  {
    glGetShaderiv(_shader_, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
      glGetShaderInfoLog(_shader_, 1024, nullptr, infoLog);
      std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
    }
  }
  else
  {
    glGetProgramiv(_shader_, GL_LINK_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
      glGetProgramInfoLog(_shader_, 1024, nullptr, infoLog);
      std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
    }
  }
}



