//
// Created by nami on 2022-02-23.
//

#include "../Include/program.h"

// Create a program for opengl to execute on screen.
Program::Program()
{
  printf("CREATING PROGRAM...");
  program = glCreateProgram();
  printf("Done.\n");
}

Program::~Program()
{
  glDeleteProgram(program);
  std::cout << "DESTROYING PROGRAM...\n";
}

// Set our shader program to attach our created shader to it (link source codes like '#include').
void Program::attach(const Shader& shader) const
{
  glAttachShader(program, shader.get_value());
}

// Links all source codes (shaders) in the program given as argument, creating the executable.
void Program::link() const {
  int success;
  char infoLog[512];
  glLinkProgram(program);
  // check for linking errors
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }
}

void Program::validate() const {
  glValidateProgram(program);
}

GLuint Program::get_program() const {
  return program;
}

void Program::activate() const {
  glUseProgram(program);
}
