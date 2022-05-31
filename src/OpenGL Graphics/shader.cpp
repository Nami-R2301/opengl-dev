//
// Created by nami on 2022-02-23.
//
#include "../../Include/OpenGL Graphics/shader.h"

#define PROGRAM_ERROR -5
#define COMPILE_ERROR -6
#define LINK_ERROR -7

Shader::Shader()
{
  this->uniforms = std::map<const char *, int>();
}

[[maybe_unused]] const char *Shader::get_fragment_source() const
{
  return this->fragment_source;
}

[[maybe_unused]] const char *Shader::get_vertex_source() const
{
  return this->vertex_source;
}

[[maybe_unused]] void Shader::set_fragment_source(const char *file_path)
{
  this->fragment_source = Resource_loader::load_shader_source(file_path).c_str();
}

[[maybe_unused]] void Shader::set_vertex_source(const char *file_path)
{
  this->vertex_source = Resource_loader::load_shader_source(file_path).c_str();
}

void Shader::setup_basic_shader()
{
  // Init opengl memory buffers and shaders.
  create_program();
  add_shader(GL_VERTEX_SHADER,
             Resource_loader::load_shader_source("default.vert").c_str());
  add_shader(GL_FRAGMENT_SHADER,
             Resource_loader::load_shader_source("default.frag").c_str());
  link();
}

GLuint Shader::get_program() const
{
  return program;
}

void Shader::create_program()
{
  Logger::alert(INFO, "CREATING PROGRAM...");
  program = glCreateProgram();
  if (!program)
  {
    Logger::alert(ERROR, "ERROR : COULD NOT CREATE PROGRAM!\tEXITING...");
    exit(PROGRAM_ERROR);
  }
}

void Shader::add_shader(int type, const char *source) const
{
  Logger::alert(INFO, "CREATING, SOURCING AND COMPILING SHADER : %d...", type);

  GLuint shader = glCreateShader(type);
  Shader::source(shader, source, nullptr);
  Shader::compile(shader, type);
  attach(shader);
}

//Set the source code in program to the source code in the array of strings specified by string.
void Shader::source(GLuint shader_, const char *source, int *length)
{
  glShaderSource(shader_, 1, &source, length);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "SHADER.CPP", 84);  // check errors.
}

// Compile the shaders into machine code to pass on to the GPU.
void Shader::compile(GLuint shader, GLuint shader_type)
{
  glCompileShader(shader);
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
      Logger::alert(ERROR, "\nERROR : SHADER COMPILATION ERROR FOR SHADER OF TYPE %s\n"
                           "DETAILS :\n%s", type, infoLog);
      exit(COMPILE_ERROR);
    }
  }
}

// Set our program to attach our created program to it (link source codes like '#include').
void Shader::attach(GLuint shader) const
{
  glAttachShader(Shader::get_program(), shader);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "SHADER.CPP", 132);  // check errors.
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
    Logger::alert(ERROR, "\nERROR : SHADER LINKING ERROR\n"
                         "DETAILS :\n%s", infoLog);
    exit(LINK_ERROR);
  }
  validate();
}

void Shader::validate() const
{
  glValidateProgram(get_program());
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "SHADER.CPP", 163);  // check errors.
}

void Shader::activate() const
{
  glUseProgram(program);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "SHADER.CPP", 169);  // check errors.
}

void Shader::delete_shader() const
{
  Logger::alert(INFO, "DESTROYING SHADERS...");
  glDeleteShader(this->get_program());
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "SHADER.CPP", 176);  // check errors.
}

void Shader::add_uniform(const char *uniform)
{
  int uniform_location = glGetUniformLocation(this->program, uniform);
  if (uniform_location < 0)
    Logger::alert(ERROR, "ERROR : COULD NOT FIND UNIFORM : %s", uniform);
  else this->uniforms.emplace(uniform, uniform_location);
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, int value)
{
  glUniform1i(this->uniforms[uniform_name], value);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) Render::gl_error_callback(error, "SHADER.CPP", 199);
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, float value)
{
  glUniform1f(this->uniforms[uniform_name], value);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) Render::gl_error_callback(error, "SHADER.CPP", 206);
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, const Vector_3f &vector_3f)
{
  glUniform3f(this->uniforms[uniform_name], vector_3f.get_x(),
              vector_3f.get_y(),
              vector_3f.get_z());
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) Render::gl_error_callback(error, "SHADER.CPP", 215);
}

void Shader::set_uniform(const char *uniform_name, const Matrix_4f &value)
{
  glUniformMatrix4fv(this->uniforms[uniform_name], 1,
                     GL_TRUE, &value.get_matrix()[0][0]);
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) Render::gl_error_callback(error, "SHADER.CPP", 223);
}

[[maybe_unused]] void Shader::set_uniform(const char *uniform_name, const Color &color)
{
  glUniform4f(this->uniforms[uniform_name],
              color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) Render::gl_error_callback(error, "SHADER.CPP", 231);
}

//void Shader::update_uniforms(const Matrix_4f &world_matrix, Matrix_4f projected_matrix,
//                             const Material &material)
//{
//  // Set program uniforms.
//  set_uniform("color", material.get_color());
//  set_uniform("transform", projected_matrix);
//}

void Shader::cleanup()
{
  delete_shader();
  this->uniforms.clear();
}



