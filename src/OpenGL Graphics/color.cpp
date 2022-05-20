//
// Created by nami on 2022-02-23.
//
#include "../../Include/OpenGL Graphics/color.h"

Color::Color(float red, float green, float blue, float alpha)
{
  if ((red <= 1.0f && red >= 0.0f) && (green <= 1.0f && green >= 0.0f) && (blue <= 1.0f && blue >= 0.0f)
      && (alpha <= 1.0f && alpha >= 0.0f))
  {
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;
  } else if ((red > 1.0f || red < 0.0f) || (green > 1.0f || green < 0.0f) || (blue > 1.0f || blue < 0.0f))
    normalize();
}

[[maybe_unused]] Color::Color(const rgb_color_s &RGB_value)
{
  color.red = RGB_value.red;
  color.green = RGB_value.green;
  color.blue = RGB_value.blue;
  color.alpha = RGB_value.alpha;
  if ((RGB_value.red > 1.0f || RGB_value.red < 0.0f) || (RGB_value.green > 1.0f || RGB_value.green < 0.0f)
      || (RGB_value.blue > 1.0f || RGB_value.blue < 0.0f))
    normalize();
}

// Reset the color.
void Color::clear()
{
  const Color new_color; // Default color (Dark gray).
  *this = new_color;
}

[[maybe_unused]] rgb_color_s &Color::get_rgb_values()
{
  return color;
}

float Color::get_red() const
{
  return color.red;
}

float Color::get_blue() const
{
  return color.blue;
}

float Color::get_green() const
{
  return color.green;
}

float Color::get_alpha() const
{
  return color.alpha;
}

[[maybe_unused]] Color::Color(const Color &new_color)
{
  if (this == &new_color) return;
  this->color = new_color.color;
}

[[maybe_unused]] void Color::print() const
{
  char buffer[256];
  if (snprintf(buffer, 256,
               "Red value : %.2f\nGreen value : %.2f\nBlue value : %.2f\nAlpha value : %.2f\n",
               color.red, color.green, color.blue, color.alpha) < 0)
  {
    Logger::alert("ERROR WHEN FORMATTING STRING (SNPRINTF)!\nEXITING...\n", ERROR);
    exit(ERROR_SNPRINTF);
  }

  Logger::alert(buffer);
}

[[maybe_unused]] void Color::set_color(const Color &new_color)
{
  *this = new_color;
}

[[maybe_unused]] void Color::set_color(float red, float green, float blue, float alpha)
{
  this->color.red = red;
  this->color.green = green;
  this->color.blue = blue;
  this->color.alpha = alpha;
}

void *Color::operator new(unsigned long size)
{
  auto *new_color = (Color *) malloc(size);
  if (new_color == nullptr)
  {
    Logger::alert("NOT ENOUGH MEMORY ON THE HEAP\n", ERROR);
    exit(-11);
  }
  new_color->color.red = 0.0f;
  new_color->color.green = 0.0f;
  new_color->color.blue = 0.0f;
  new_color->color.alpha = 0.0f;
  return new_color;
}

Color &Color::operator=(const Color &other_color)
{
  if (this == &other_color) return *this;
  this->color = other_color.color;
  return *this;
}

bool Color::operator==(const Color &other_color)
{
  if (this == &other_color) return true;
  return (this->color.red == other_color.get_red() &&
          this->color.green == other_color.get_green() &&
          this->color.blue == other_color.get_blue() &&
          this->color.alpha == other_color.get_alpha());
}

void Color::operator delete(void *color)
{
  if (color != nullptr) free(color);
}

void Color::normalize()
{
  float min = 0.0f, max = 1.0f;
  this->color.red = (get_red() - min) / (max - min);
  this->color.green = (get_green() - min) / (max - min);
  this->color.blue = (get_blue() - min) / (max - min);
  this->color.alpha = (get_alpha() - min) / (max - min);
}
