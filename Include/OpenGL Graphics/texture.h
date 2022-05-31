//
// Created by nami on 5/26/22.
//

#ifndef OPENGL_DEV_TEXTURE_H
#define OPENGL_DEV_TEXTURE_H

#include "render.h"

class Texture
{
public:
  Texture();
  explicit Texture(const char *file_path);

  [[nodiscard]] GLuint get_id() const;
  void set_id(int id_texture);
  void set_local_buffer(unsigned char *local_buffer);
  int get_width() const;
  void set_width(int width);
  int get_height() const;
  void set_height(int height);
  int get_bits_per_pixel() const;
  void set_bits_per_pixel(int bits_per_pixel);
  unsigned char *get_local_buffer() const;

  Texture &operator=(const Texture &other_texture);
private:
  GLuint id = 0;
  unsigned char *local_buffer = nullptr;
  int width = 0;
  int height = 0;
  int bits_per_pixel = 0;
};

#endif //OPENGL_DEV_TEXTURE_H
