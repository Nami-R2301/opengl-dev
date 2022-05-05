//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_COLOR_H
#define OPENGL_DEV_COLOR_H
#include <GLES3/gl3.h>

// Setup our RGB structure.
struct rgb_color_s {
  float red = 0.0f;
  float green = 0.0f;
  float blue = 0.0f;
  float alpha = 0.0f;
};

// Set custom colors for the background or for fragments.
class Color
{
public:
  explicit Color(float = 0.156862745f, float = 0.156862745f, float = 0.156862745f, float = 0.0f); // Dark gray.
  [[maybe_unused]] explicit Color(const rgb_color_s &);

  ~Color();

  [[maybe_unused]] Color(const Color&);
  void clear();
  rgb_color_s& get_rgb_values();
  [[nodiscard]] float get_red() const;
  [[nodiscard]] float get_blue() const;
  [[nodiscard]] float get_green() const;
  [[nodiscard]] float get_alpha() const;
  Color& operator =(const Color&);

private:
  rgb_color_s color;
};


#endif //OPENGL_DEV_COLOR_H
