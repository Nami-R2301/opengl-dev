//
// Created by nami on 2022-02-23.
//

#define MAX 255.0f

#include "../../Include/OpenGL Graphics//color.h"

Color::Color(float red, float green, float blue, float alpha)
{
  if ((red <= 1.0f && red >= 0.0f) && (green <= 1.0f && green >= 0.0f) && (blue <= 1.0f && blue >= 0.0f)
      && (alpha <= 1.0f && alpha >= 0.0f))
  {
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;
  } else if (red > 1.0f || green > 1.0f || blue > 1.0f)
  {
    color.red /= MAX; // Normalise the value between 0 and 1.
    color.green /= MAX;
    color.blue /= MAX;
    color.alpha = 1.0f;
  } else if ((red < 0.0f && red >= -1.0f) || (green < 0.0f && green >= -1.0f)
             || (blue < 0.0f && blue >= -1.0f))
  {
    color.red = 0 - red;
    color.green = 0 - green;
    color.blue = 0 - blue;
    color.alpha = 1.0f;
  }
}

[[maybe_unused]] Color::Color(const rgb_color_s &RGB_value)
{
  color.red = RGB_value.red;
  color.green = RGB_value.green;
  color.blue = RGB_value.blue;
  color.alpha = RGB_value.alpha;
  if (RGB_value.red > 1 && RGB_value.green > 1 && RGB_value.blue > 1)
  {
    color.red /= MAX; // Normalise the value between 0 and 1.
    color.green /= MAX;
    color.blue /= MAX;
    color.alpha = 1.0f;
  }
}

Color &Color::operator=(const Color &new_color)
{
  if (this == &new_color) return *this;
  color.red = new_color.color.red;
  color.green = new_color.color.green;
  color.blue = new_color.color.blue;
  color.alpha = new_color.color.alpha;
  return *this;
}

bool Color::operator==(const Color &new_color)
{
  if (this == &new_color) return true;
  return (color.red == new_color.get_red() && color.green == new_color.get_green()
          && color.blue == new_color.get_blue() && color.alpha == new_color.get_alpha());
}

// Reset the color of the background.
void Color::clear()
{
  const Color new_color; // Default color (Dark gray).
  *this = new_color;
}

rgb_color_s &Color::get_rgb_values()
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
  printf("Red value : %.2f\nGreen value : %.2f\nBlue value : %.2f\nAlpha value : %.2f\n",
         color.red, color.green, color.blue, color.alpha);
}

Color::~Color() = default;
