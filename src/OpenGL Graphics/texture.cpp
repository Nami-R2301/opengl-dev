//
// Created by nami on 5/26/22.
//

#include "../../Include/OpenGL Graphics/texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../../Include/Stb/stdb_image.h"

Texture::Texture() = default;

Texture::Texture(const char *file_path) : id(0), local_buffer(nullptr),
                                          width(0), height(0), bits_per_pixel(0)
{
  // Load texture in memory.
  stbi_set_flip_vertically_on_load(1);  // Invert y-axis for opengl matrix coordinates.
  local_buffer = stbi_load(file_path, &width, &height, &bits_per_pixel, 4);  // 4 channels (RGBA).

  // Initialize openGL texture buffers.
  glGenTextures(1, &id);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "TEXTURE.CPP", 22);  // check errors.

  // Initialize flags for texture buffers.
  glBindTexture(GL_TEXTURE_2D, id);
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "TEXTURE.CPP", 26);  // check errors.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // Min surface to cover.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "TEXTURE.CPP", 28);  // check errors.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Max surface to cover and extend.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "TEXTURE.CPP", 30);  // check errors.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  // Normalize x-axis of texture.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "TEXTURE.CPP", 32);  // check errors.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);  // Normalize y-axis of texture.
  if (glGetError() != 0) Render::gl_error_callback(glGetError(), "TEXTURE.CPP", 34);  // check errors.

  // Assign texture image to texture buffer.
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
               GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);

  // Deallocate texture from CPU since it's loaded onto the GPU.
  glBindTexture(GL_TEXTURE_2D, 0);  // Unbind texture since it's loaded.
  if (local_buffer)
    stbi_image_free(local_buffer);
}

GLuint Texture::get_id() const
{
  return this->id;
}

void Texture::set_id(int id_texture)
{
  this->id = id_texture;
}

unsigned char *Texture::get_local_buffer() const
{
  return local_buffer;
}

void Texture::set_local_buffer(unsigned char *local_buffer_)
{
  local_buffer = local_buffer_;
}

int Texture::get_width() const
{
  return width;
}

void Texture::set_width(int width_)
{
  Texture::width = width_;
}

int Texture::get_height() const
{
  return height;
}

void Texture::set_height(int height_)
{
  Texture::height = height_;
}

int Texture::get_bits_per_pixel() const
{
  return bits_per_pixel;
}

void Texture::set_bits_per_pixel(int bits_per_pixel_)
{
  bits_per_pixel = bits_per_pixel_;
}

Texture &Texture::operator=(const Texture &other_texture)
{
  if (this == &other_texture) return *this;
  this->id = other_texture.id;
  this->local_buffer = other_texture.local_buffer;
  this->width = other_texture.width;
  this->height = other_texture.height;
  this->bits_per_pixel = other_texture.bits_per_pixel;
  return *this;
}
