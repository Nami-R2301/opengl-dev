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
  this->fragment_source = get_file_contents(file_path).c_str();
}

[[maybe_unused]] void Shader::set_vertex_source(const char *file_path)
{
  this->vertex_source = get_file_contents(file_path).c_str();
}

GLuint Shader::get_program() const
{
  return program;
}

std::string get_file_contents(const char *filename)
{
  std::ifstream in((filename), std::ios::binary);
  if (in)
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

void Shader::create_program()
{
  Logger::alert("CREATING PROGRAM...\t");
  program = glCreateProgram();
  if (!program)
  {
    Logger::alert("ERROR : COULD NOT CREATE PROGRAM!\tEXITING...\n", ERROR, true);
    exit(PROGRAM_ERROR);
  }
  Logger::alert("Done.\n", INFO, true);
}

void Shader::add_shader(int type, const char *source) const
{
  char print_buffer[75];
  if (snprintf(print_buffer, 75, "CREATING, SOURCING AND COMPILING SHADER : %d...\t", type) < 0)
  {
    Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
    exit(ERROR_SNPRINTF);
  }
  Logger::alert(print_buffer);

  GLuint shader = glCreateShader(type);
  Shader::source(shader, source, nullptr);
  Shader::compile(shader, type);
  attach(shader);
  Logger::alert("Done.\n", INFO, true);
}

//Set the source code in program to the source code in the array of strings specified by string.
void Shader::source(GLuint shader_, const char *source, int *length)
{
  glShaderSource(shader_, 1, &source, length);
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
      char print_buffer[1300];
      if (snprintf(print_buffer, 1300, "\nERROR : SHADER COMPILATION ERROR FOR SHADER OF TYPE %s\n"
                                       "DETAILS :\n%s\n", type, infoLog) < 0)
      {
        Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
        exit(ERROR_SNPRINTF);
      }
      Logger::alert(print_buffer, ERROR);
      exit(COMPILE_ERROR);
    }
  }
}

// Set our program to attach our created program to it (link source codes like '#include').
void Shader::attach(GLuint shader) const
{
  glAttachShader(Shader::get_program(), shader);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
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
    char print_buffer[1300];
    if (snprintf(print_buffer, 1300, "\nERROR : SHADER LINKING ERROR\n"
                                     "DETAILS :\n%s\n", infoLog) < 0)
    {
      Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
      exit(ERROR_SNPRINTF);
    }
    Logger::alert(print_buffer, ERROR);
    exit(LINK_ERROR);
  }
  validate();
}

void Shader::validate() const
{
  glValidateProgram(get_program());
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

void Shader::activate() const
{
  glUseProgram(program);
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
}

[[maybe_unused]] void Shader::update_scale(const float scale) const
{
  // Update vertex_source uniform
  int vertex_scale_location = glGetUniformLocation(program, "scale");
  if (vertex_scale_location >= 0)
    glUniform1f(vertex_scale_location, scale);
  else Logger::alert("ERROR WHEN UPDATING SCALE\n", ERROR);
}

[[maybe_unused]] void Shader::update_color(const Color &new_color) const
{
  int vertex_color_location = glGetUniformLocation(program, "fragment_color");
  if (vertex_color_location >= 0)
    glUniform4f(vertex_color_location, new_color.get_red(), new_color.get_green(),
                new_color.get_blue(), new_color.get_alpha());
  else Logger::alert("ERROR WHEN UPDATING COLOR\n", ERROR);
}

void Shader::update_color(float red, float green, float blue, float alpha) const
{
  int vertex_color_location = glGetUniformLocation(program, "fragment_color");
  if (vertex_color_location >= 0)
    glUniform4f(vertex_color_location, red, green,
                blue, alpha);
  else Logger::alert("ERROR WHEN UPDATING COLOR\n", ERROR);
}

void Shader::delete_shader() const
{
  Logger::alert("DESTROYING SHADERS...\t");
  glDeleteShader(this->get_program());
  if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  Logger::alert("Done.\n", INFO, true);
}

void Shader::add_uniform(const char *uniform)
{
  int uniform_location = glGetUniformLocation(program, uniform);
  char buffer[75];
  if (uniform_location < 0)
  {
    if (snprintf(buffer, 75, "ERROR : COULD NOT FIND UNIFORM : %s", uniform) < 0)
    {
      Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
      exit(ERROR_SNPRINTF);
    }
    Logger::alert(buffer, ERROR);
  } else this->uniforms.emplace(uniform, uniform_location);
}

void Shader::set_uniform(const char *uniform_name, int value)
{
  glUniform1i(this->uniforms[uniform_name], value);
}

void Shader::set_uniform(const char *uniform_name, float value)
{
  glUniform1f(this->uniforms[uniform_name], value);
}

void Shader::set_uniform(const char *uniform_name, const Vector_3f &vector_3f)
{
  glUniform3f(this->uniforms[uniform_name], vector_3f.get_x(),
              vector_3f.get_y(),
              vector_3f.get_z());
}

void Shader::set_uniform(const char *uniform_name, const Matrix4f &value)
{
  glUniformMatrix4fv(this->uniforms[uniform_name], value.length(),
                     true, value.get_matrix());
}



