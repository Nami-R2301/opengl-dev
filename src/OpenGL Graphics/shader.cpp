//
// Created by nami on 2022-02-23.
//
#include "../../Include/OpenGL Graphics/shader.h"

#define PROGRAM_ERROR -5
#define COMPILE_ERROR -6
#define LINK_ERROR -7

Shader::Shader()
{
  output_on_screen("CREATING PROGRAM...\t");
  program = glCreateProgram();
  if (!program)
  {
    output_on_screen("\nERROR : COULD NOT CREATE PROGRAM!\nEXITING...\n", ERROR);
    exit(PROGRAM_ERROR);
  }
  output_on_screen("Done.\n", INFO, true);
}

//Set the source code in shader to the source code in the array of strings specified by string.
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
      snprintf(print_buffer, 1300, "\nERROR : SHADER COMPILATION ERROR FOR SHADER OF TYPE %s\n"
                                   "DETAILS :\n%s\n", type, infoLog);
      output_on_screen(print_buffer, ERROR);
      exit(COMPILE_ERROR);
    }
  }
}

// Set our shader program to attach our created shader to it (link source codes like '#include').
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
    snprintf(print_buffer, 1300, "\nERROR : SHADER LINKING ERROR\n"
                                 "DETAILS :\n%s\n", infoLog);
    output_on_screen(print_buffer, ERROR);
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
  // Update vertex uniform
  int vertex_scale_location = glGetUniformLocation(program, "scale");
  if (vertex_scale_location >= 0)
    glUniform1f(vertex_scale_location, scale);
  else output_on_screen("ERROR WHEN UPDATING SCALE\n", ERROR);
}

void Shader::update_color(const Color &new_color) const
{
  int vertex_color_location = glGetUniformLocation(program, "fragment_color");
  if (vertex_color_location >= 0)
    glUniform4f(vertex_color_location, new_color.get_red(), new_color.get_green(),
                new_color.get_blue(), new_color.get_alpha());
  else output_on_screen("ERROR WHEN UPDATING COLOR\n", ERROR);
}

std::vector<GLuint> Shader::get_shaders() const
{
  return this->shaders;
}

std::string Shader::get_shader_source(const char *shader_path)
{
  std::string source = get_file_contents(shader_path);
  return source;
}

void Shader::add_shader(int type, const char *source) const
{
  char print_buffer[75];
  snprintf(print_buffer, 75, "CREATING, SOURCING AND COMPILING SHADER : %d...\t", type);
  output_on_screen(print_buffer);

  GLuint shader = glCreateShader(type);
  get_shaders().push_back(shader);
  Shader::source(shader, source, nullptr);
  Shader::compile(shader, type);
  attach(shader);
  output_on_screen("Done.\n", INFO, true);
}

void Shader::delete_shaders() const
{
  output_on_screen("DESTROYING SHADERS...\t");
  for (unsigned int shader: get_shaders())
  {
    glDeleteShader(shader);
    if (glGetError() != 0) Render::gl_error_callback(glGetError());  // check errors.
  }
  output_on_screen("Done.\n", INFO, true);
}



