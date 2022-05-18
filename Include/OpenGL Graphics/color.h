//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_COLOR_H
#define OPENGL_DEV_COLOR_H

#include <GLES3/gl3.h>
#include "../../Include/Logs/logger.h"

#define MAX 255.0f

// Setup our RGB structure.
struct rgb_color_s
{
  float red = 0.0f;
  float green = 0.0f;
  float blue = 0.0f;
  float alpha = 0.0f;
};

// Set custom colors for the background or for fragments.
class Color
{
public:
  explicit Color(float = 0.156862745f, float = 0.156862745f, float = 0.156862745f, float = 1.0f); // Dark gray.
  [[maybe_unused]] explicit Color(const rgb_color_s &);
  [[maybe_unused]] Color(const Color &);
  [[nodiscard]] float get_red() const;
  [[nodiscard]] float get_blue() const;
  [[nodiscard]] float get_green() const;
  [[nodiscard]] float get_alpha() const;
  [[maybe_unused]] rgb_color_s &get_rgb_values();
  [[maybe_unused]] void set_color(const Color &new_color);
  [[maybe_unused]] void set_color(float red, float blue, float green, float alpha);
  void clear();
  [[maybe_unused]] void print() const;
  void *operator new(unsigned long size);
  void operator delete(void *color);
  Color &operator=(const Color &other_color);
  bool operator==(const Color &other_color);

private:
  rgb_color_s color;
};

#endif //OPENGL_DEV_COLOR_H
