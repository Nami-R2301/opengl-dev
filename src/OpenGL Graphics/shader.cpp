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
  this->uniforms = std::unordered_map<const char *, int>();
}

Shader::Shader(const char *vertex_file_path, const char *fragment_file_path)
{
  this->uniforms = std::unordered_map<const char *, int>();
  // Init opengl memory buffers and shaders.
  create_program();
  add_shader(GL_VERTEX_SHADER, vertex_file_path);
  add_shader(GL_FRAGMENT_SHADER, fragment_file_path);
  link();
}

unsigned int Shader::get_program() const
{
  return m_renderer_id;
}

void Shader::create_program()
{
  alert(INFO, "CREATING PROGRAM...");
  gl_call(m_renderer_id = glCreateProgram());
  if (m_renderer_id <= GL_FALSE)
  {
    alert(ERROR, "ERROR : COULD NOT CREATE PROGRAM!\tEXITING...");
    exit(PROGRAM_ERROR);
  }
}

void Shader::add_shader(int type, const char *source) const
{
  alert(INFO, "CREATING, SOURCING AND COMPILING SHADER : %d...", type);

  gl_call(unsigned int shader = glCreateShader(type));
  Shader::source(shader, source, nullptr);
  Shader::compile(shader, type);
  attach(shader);
}

//Set the parse_shader code in m_renderer_id to the parse_shader code in the array of strings specified by string.
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
  int hasCompiled;
  // Character array to store error message in
  char infoLog[1024];
  if (strcmp(type, "PROGRAM") != 0)
  {
    gl_call(glGetShaderiv(_shader_, GL_COMPILE_STATUS, &hasCompiled));
    if (hasCompiled <= GL_FALSE)
    {
      glGetShaderInfoLog(_shader_, 1024, nullptr, infoLog);
      alert(ERROR, "\nERROR : SHADER COMPILATION ERROR FOR SHADER OF TYPE %s\n"
                   "DETAILS :\n%s", type, infoLog);
      exit(COMPILE_ERROR);
    }
  }
}

// Set our m_renderer_id to attach our created m_renderer_id to it (link parse_shader codes like '#include').
void Shader::attach(unsigned int shader) const
{
  gl_call(glAttachShader(Shader::get_program(), shader));
}

// Links all parse_shader codes (shaders) in the m_renderer_id given as argument, creating the executable.
void Shader::link() const
{
  // Stores status of compilation
  int has_linked;
  char infoLog[512];
  gl_call(glLinkProgram(get_program()));
  // check for linking errors
  gl_call(glGetProgramiv(get_program(), GL_LINK_STATUS, &has_linked));
  if (has_linked <= GL_FALSE)
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
  gl_call(glUseProgram(m_renderer_id));
}

void Shader::deactivate()
{
  gl_call(glUseProgram(0));
}

int Shader::get_uniform_location(const char *uniform)
{
  // Caching uniforms.
  if (this->uniforms.find(uniform) != this->uniforms.end()) return this->uniforms[uniform];
  add_uniform(uniform);
  return this->uniforms[uniform];
}

void Shader::add_uniform(const char *uniform)
{
  if (this->uniforms.find(uniform) != this->uniforms.end()) return;  // If found, don't add it.
  int uniform_location = glGetUniformLocation(this->m_renderer_id, uniform);
  if (uniform_location < 0) alert(ERROR, "ERROR : COULD NOT FIND UNIFORM : %s", uniform);
  this->uniforms.emplace(uniform, uniform_location);  // If not found, create it.
}

void Shader::set_uniform(const char *uniform_name, const Matrix_4f &value)
{
  gl_call(glUniformMatrix4fv(get_uniform_location(uniform_name), 1,
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
  gl_call(glUniform1i(get_uniform_location(uniform_name), value));
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, float value)
{
  gl_call(glUniform1f(get_uniform_location(uniform_name), value));
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, const Vector_3f &vector_3f)
{
  gl_call(glUniform3f(get_uniform_location(uniform_name), vector_3f.get_x(),
                      vector_3f.get_y(),
                      vector_3f.get_z()));
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, const Color &color)
{
  gl_call(glUniform4f(get_uniform_location(uniform_name),
                      color.get_red(), color.get_green(), color.get_blue(), color.get_alpha()));
}



