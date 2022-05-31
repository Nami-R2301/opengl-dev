//
// Created by nami on 5/30/22.
//

#include "../../Include/OpenGL Graphics/material.h"

Material::Material(const Texture &texture, const Color &color)
{
  this->texture = texture;
  this->color = color;
}

const Texture &Material::get_texture() const
{
  return texture;
}

void Material::set_texture(const Texture &texture_)
{
  Material::texture = texture_;
}

const Color &Material::get_color() const
{
  return color;
}

void Material::set_color(const Color &color_)
{
  Material::color = color_;
}
