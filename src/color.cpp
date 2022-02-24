//
// Created by nami on 2022-02-23.
//

#define MAX 255.0f
#include "../Include/color.h"

Color::Color(float red, float green, float blue, float alpha)
{
  if(red <= 1 && green <= 1 && blue <= 1 && alpha <= 1)
  {
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;
  }
}

Color::Color(const rgb_color_s & RGB_value)
{
  color.red = RGB_value.red;
  color.green = RGB_value.green;
  color.blue = RGB_value.blue;
  color.alpha = RGB_value.alpha;
  if(RGB_value.red > 1 && RGB_value.green > 1 && RGB_value.blue > 1 && RGB_value.alpha > 1)
  {
  color.red /= MAX; // Normalise the value between 0 and 1.
  color.green /= MAX;
  color.blue /= MAX;
  color.alpha /= MAX;
  }
}

Color& Color::operator=(const Color& new_color)
{
  if(this == &new_color) return *this;
  color.red = new_color.color.red;
  color.green = new_color.color.green;
  color.blue = new_color.color.blue;
  color.alpha = new_color.color.alpha;
  return *this;
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
