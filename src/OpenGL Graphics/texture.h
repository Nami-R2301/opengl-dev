//
// Created by nami on 5/26/22.
//

#ifndef OPENGL_DEV_TEXTURE_H
#define OPENGL_DEV_TEXTURE_H

#include "renderer.h"

class Texture
{
public:
  Texture();
  explicit Texture(const char *file_path);

  [[maybe_unused]] [[nodiscard]] unsigned int get_id() const;
  Texture &operator=(const Texture &other_texture);

  [[maybe_unused]] void set_id(int id_texture);
  [[maybe_unused]] void set_local_buffer(unsigned char *local_buffer);
  [[maybe_unused]] int get_width() const;
  [[maybe_unused]] void set_width(int width);
  [[maybe_unused]] int get_height() const;
  [[maybe_unused]] void set_height(int height);
  [[maybe_unused]] int get_bits_per_pixel() const;
  [[maybe_unused]] void set_bits_per_pixel(int bits_per_pixel);
  [[maybe_unused]] unsigned char *get_local_buffer() const;

  void bind(unsigned int slot_) const;
  void unbind() const;
  void delete_texture() const;
private:
  unsigned int id = 0;
  unsigned char *local_buffer = nullptr;
  int width = 0;
  int height = 0;
  int bits_per_pixel = 0;
};

#endif //OPENGL_DEV_TEXTURE_H
