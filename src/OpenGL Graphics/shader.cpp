//
// Created by nami on 2022-02-23.
//
#include "../../Include/OpenGL Graphics/shader.h"

#define PROGRAM_ERROR -5
#define COMPILE_ERROR -6
#define LINK_ERROR -7

Shader::Shader()
{
  printf("CREATING PROGRAM...");
  program = glCreateProgram();
  if (!program)
  {
    fprintf(stderr, "\nERROR : COULD NOT CREATE PROGRAM!\nEXITING...\n");
    exit(PROGRAM_ERROR);
  }
  printf("Done.\n");
}

// Delete the shaders since they have been compiled and linked in the program.
//Shader::~Shader() = default;

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
      fprintf(stderr, "\nERROR : SHADER COMPILATION ERROR FOR SHADER OF TYPE %s\n"
                      "DETAILS :\n%s\n", type, infoLog);
      exit(COMPILE_ERROR);
    }
  }
}

// Set our shader program to attach our created shader to it (link source codes like '#include').
void Shader::attach(GLuint shader) const
{
  glAttachShader(Shader::get_program(), shader);
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
    fprintf(stderr, "\nERROR : SHADER LINKING ERROR\n"
                    "DETAILS :\n%s\n", infoLog);
    exit(LINK_ERROR);
  }
  validate();
}

void Shader::validate() const
{
  glValidateProgram(get_program());
}

void Shader::activate() const
{
  glUseProgram(program);
}

void Shader::update_scale(const float scale) const
{
  // Update vertex uniform
  int vertex_scale_location = glGetUniformLocation(program, "scale");
  if (vertex_scale_location >= 0)
    glUniform1f(vertex_scale_location, scale);
  else fprintf(stderr, "ERROR WHEN UPDATING SCALE\n");
}

void Shader::update_color(const Color &new_color) const
{
  int vertex_color_location = glGetUniformLocation(program, "fragment_color");
  if (vertex_color_location >= 0)
    glUniform4f(vertex_color_location, new_color.get_red(), new_color.get_green(),
                new_color.get_blue(), new_color.get_alpha());
  else fprintf(stderr, "ERROR WHEN UPDATING COLOR\n");
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
  printf("CREATING, SOURCING AND COMPILING SHADER : %d...\t", type);
  GLuint shader = glCreateShader(type);
  get_shaders().push_back(shader);
  Shader::source(shader, source, nullptr);
  Shader::compile(shader, type);
  attach(shader);
  printf("Done.\n");
}

void Shader::delete_shaders() const
{
  printf("DESTROYING SHADERS ...\t");
  for (unsigned int shader: get_shaders()) glDeleteShader(shader);
  printf("Done.\n");
}



