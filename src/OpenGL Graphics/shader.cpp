//
// Created by nami on 2022-02-23.
//
#include "shader.h"
#include "res_loader.h"
#include "../Logs/logger.h"
#include "renderer.h"

#define PROGRAM_ERROR -5
#define COMPILE_ERROR -6
#define LINK_ERROR -7

Shader::Shader()
{
  this->uniforms = std::map<const char *, int>();
}

void Shader::setup_basic_shader()
{
  // Init opengl memory buffers and shaders.
  create_program();
  add_shader(GL_VERTEX_SHADER, load_shader_source("default.vert").c_str());
  add_shader(GL_FRAGMENT_SHADER, load_shader_source("default.frag").c_str());
  link();
}

GLuint Shader::get_program() const
{
  return program;
}

void Shader::create_program()
{
  alert(INFO, "CREATING PROGRAM...");
  program = glCreateProgram();
  if (!program)
  {
    alert(ERROR, "ERROR : COULD NOT CREATE PROGRAM!\tEXITING...");
    exit(PROGRAM_ERROR);
  }
}

void Shader::add_shader(int type, const char *source) const
{
  alert(INFO, "CREATING, SOURCING AND COMPILING SHADER : %d...", type);

  GLuint shader = glCreateShader(type);
  Shader::source(shader, source, nullptr);
  Shader::compile(shader, type);
  attach(shader);
}

//Set the source code in program to the source code in the array of strings specified by string.
void Shader::source(GLuint shader_, const char *source, int *length)
{
  gl_call(glShaderSource(shader_, 1, &source, length));
}

// Compile the shaders into machine code to pass on to the GPU.
void Shader::compile(GLuint shader, GLuint shader_type)
{
  gl_call(glCompileShader(shader));
  if (shader_type == GL_VERTEX_SHADER)
  {
    // Checks if Shader compiled successfully
    compile_errors(shader, "VERTEX");
  } else
  {
    // Checks if Shader compiled successfully
    compile_errors(shader, "FRAGMENT");
  }
}

// Checks if the different Shaders have compiled properly
void Shader::compile_errors(unsigned int _shader_, const char *type)
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
      alert(ERROR, "\nERROR : SHADER COMPILATION ERROR FOR SHADER OF TYPE %s\n"
                   "DETAILS :\n%s", type, infoLog);
      exit(COMPILE_ERROR);
    }
  }
}

// Set our program to attach our created program to it (link source codes like '#include').
void Shader::attach(GLuint shader) const
{
  gl_call(glAttachShader(Shader::get_program(), shader));
}

// Links all source codes (shaders) in the program given as argument, creating the executable.
void Shader::link() const
{
  // Stores status of compilation
  GLint has_linked;
  char infoLog[512];
  glLinkProgram(get_program());
  // check for linking errors
  glGetProgramiv(get_program(), GL_LINK_STATUS, &has_linked);
  if (has_linked == GL_FALSE)
  {
    glGetProgramInfoLog(get_program(), 1024, nullptr, infoLog);
    alert(ERROR, "\nERROR : SHADER LINKING ERROR\n"
                 "DETAILS :\n%s", infoLog);
    exit(LINK_ERROR);
  }
  validate();
}

void Shader::validate() const
{
  gl_call(glValidateProgram(get_program()));
}

void Shader::activate() const
{
  gl_call(glUseProgram(program));
}

void Shader::deactivate()
{
  gl_call(glUseProgram(0));
}

void Shader::add_uniform(const char *uniform)
{
  int uniform_location = glGetUniformLocation(this->program, uniform);
  if (uniform_location < 0)
    alert(ERROR, "ERROR : COULD NOT FIND UNIFORM : %s", uniform);
  else this->uniforms.emplace(uniform, uniform_location);
}

void Shader::set_uniform(const char *uniform_name, const Matrix_4f &value)
{
  gl_call(glUniformMatrix4fv(this->uniforms[uniform_name], 1,
                             GL_TRUE, &value.get_matrix()[0][0]));
}

void Shader::cleanup()
{
  delete_shader();
  this->uniforms.clear();
}

void Shader::delete_shader() const
{
  alert(INFO, "DESTROYING SHADERS...");
  gl_call(glDeleteShader(this->get_program()));
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, int value)
{
  gl_call(glUniform1i(this->uniforms[uniform_name], value));
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, float value)
{
  gl_call(glUniform1f(this->uniforms[uniform_name], value));
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, const Vector_3f &vector_3f)
{
  gl_call(glUniform3f(this->uniforms[uniform_name], vector_3f.get_x(),
                      vector_3f.get_y(),
                      vector_3f.get_z()));
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, const Color &color)
{
  gl_call(glUniform4f(this->uniforms[uniform_name],
                      color.get_red(), color.get_green(), color.get_blue(), color.get_alpha()));
}



