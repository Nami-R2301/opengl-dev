//
// Created by nami on 5/26/22.
//

#include "texture.h"
#include "renderer.h"
#include "../Logs/logger.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../Vendor/Stb/stdb_image.h"

Texture::Texture() = default;

Texture::Texture(const char *file_path) : m_renderer_id(0), width(0), height(0), bits_per_pixel(0)
{
  // Load texture in memory.
  stbi_set_flip_vertically_on_load(1);  // Invert y-axis for opengl matrix coordinates.
  local_buffer = stbi_load(file_path, &width, &height, &bits_per_pixel, 4);  // 4 channels (RGBA).

  // Initialize openGL texture buffers.
  gl_call(glGenTextures(1, &m_renderer_id));

  // Initialize flags for texture buffers.
  gl_call(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
  gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));  // Min surface to cover.
  gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));  // Max surface to cover and extend.
  gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP));  // Normalize x-axis of texture.
  gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP));  // Normalize y-axis of texture.

  // Assign texture image to texture buffer.
  gl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
                       GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));

  // Deallocate texture from CPU since it's loaded onto the GPU.
  gl_call(glBindTexture(GL_TEXTURE_2D, 0));  // Unbind texture since it's loaded.
  if (local_buffer)
    stbi_image_free(local_buffer);
}

void Texture::bind(unsigned int slot_) const
{
  gl_call(glActiveTexture(GL_TEXTURE0 + slot_));  // Set our active texture slot.
  gl_call(glBindTexture(GL_TEXTURE_2D, this->m_renderer_id));
}

void Texture::unbind() const  // NOLINT
{
  gl_call(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::delete_texture() const
{
  alert(INFO, "DESTROYING TEXTURE...");
  gl_call(glDeleteTextures(1, &this->m_renderer_id));
}

[[maybe_unused]] unsigned int Texture::get_id() const
{
  return this->m_renderer_id;
}

Texture &Texture::operator=(const Texture &other_texture)
{
  if (this == &other_texture) return *this;
  this->m_renderer_id = other_texture.m_renderer_id;
  this->local_buffer = other_texture.local_buffer;
  this->width = other_texture.width;
  this->height = other_texture.height;
  this->bits_per_pixel = other_texture.bits_per_pixel;
  return *this;
}

[[maybe_unused]] void Texture::set_id(int id_texture)
{
  this->m_renderer_id = id_texture;
}

[[maybe_unused]] unsigned char *Texture::get_local_buffer() const
{
  return local_buffer;
}

[[maybe_unused]] void Texture::set_local_buffer(unsigned char *local_buffer_)
{
  local_buffer = local_buffer_;
}

[[maybe_unused]] int Texture::get_width() const
{
  return width;
}

[[maybe_unused]] void Texture::set_width(int width_)
{
  Texture::width = width_;
}

[[maybe_unused]] int Texture::get_height() const
{
  return height;
}

[[maybe_unused]] void Texture::set_height(int height_)
{
  Texture::height = height_;
}

[[maybe_unused]] int Texture::get_bits_per_pixel() const
{
  return bits_per_pixel;
}

[[maybe_unused]] void Texture::set_bits_per_pixel(int bits_per_pixel_)
{
  bits_per_pixel = bits_per_pixel_;
}
