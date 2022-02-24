//
// Created by nami on 2022-02-23.
//

#include "../Include/program.h"

// Create a program for opengl to execute on screen.
Program::Program()
{
  program = glCreateProgram();
}

Program::~Program()
{
  glDeleteProgram(program);
}

// Set our shader program to attach our created shader to it (link source codes like '#include').
void Program::attach(const Shader& shader) const
{
  glAttachShader(program, shader.get_value());
}

// Links all source codes (shaders) in the program given as argument, creating the executable.
void Program::link() const
{
  glLinkProgram(program);
}

GLuint Program::get_program() const
{
  return program;
}

void Program::activate() const
{
  glUseProgram(program);
}
