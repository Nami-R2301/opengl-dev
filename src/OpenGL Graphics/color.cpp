//
// Created by nami on 2022-02-23.
//
#include "../../Include/OpenGL Graphics/color.h"

Color::Color(float red, float green, float blue, float alpha)
{
  if ((red <= 1.0f && red >= 0.0f) && (green <= 1.0f && green >= 0.0f) && (blue <= 1.0f && blue >= 0.0f)
      && (alpha <= 1.0f && alpha >= 0.0f))
  {
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
  } else if ((red > 1.0f || red < 0.0f) || (green > 1.0f || green < 0.0f) || (blue > 1.0f || blue < 0.0f))
    normalize();
}

// Reset the this->
void Color::clear()
{
  const Color new_color; // Default color (Dark gray).
  *this = new_color;
}

float Color::get_red() const
{
  return this->red;
}

float Color::get_blue() const
{
  return this->blue;
}

float Color::get_green() const
{
  return this->green;
}

float Color::get_alpha() const
{
  return this->alpha;
}

[[maybe_unused]] Color::Color(const Color &new_color)
{
  if (this == &new_color) return;
  *this = new_color;
}

[[maybe_unused]] void Color::print() const
{
  char buffer[256];
  if (snprintf(buffer, 256,
               "Red value : %.2f\nGreen value : %.2f\nBlue value : %.2f\nAlpha value : %.2f\n",
               this->red, this->green, this->blue, this->alpha) < 0)
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

[[maybe_unused]] void Color::set_color(float red_, float green_, float blue_, float alpha_)
{
  this->red = red_;
  this->green = green_;
  this->blue = blue_;
  this->alpha = alpha_;
}

Color &Color::operator=(const Color &other_color)
{
  if (this == &other_color) return *this;
  this->red = other_color.red;
  this->blue = other_color.blue;
  this->green = other_color.green;
  this->alpha = other_color.alpha;
  return *this;
}

bool Color::operator==(const Color &other_color)
{
  if (this == &other_color) return true;
  return (this->red == other_color.red &&
          this->green == other_color.green &&
          this->blue == other_color.blue &&
          this->alpha == other_color.alpha);
}

void Color::normalize()
{
  float min = 0.0f, max = 1.0f;
  this->red = (get_red() - min) / (max - min);
  this->green = (get_green() - min) / (max - min);
  this->blue = (get_blue() - min) / (max - min);
  this->alpha = (get_alpha() - min) / (max - min);
}
