//
// Created by nami on 5/30/22.
//

#ifndef OPENGL_DEV_MATERIAL_H
#define OPENGL_DEV_MATERIAL_H

#include "texture.h"

class Material
{
public:
  Material() = default;
  Material(const Texture &texture, const Color &color);
  const Texture &get_texture() const;
  void set_texture(const Texture &texture);
  const Color &get_color() const;
  void set_color(const Color &color);
private:
  Texture texture;
  Color color;
};

#endif //OPENGL_DEV_MATERIAL_H
