//
// Created by nami on 2022-02-23.
//

#ifndef OPENGL_DEV_COLOR_H
#define OPENGL_DEV_COLOR_H

#define COLOR_SIZE sizeof(float) * 4

// Set custom colors for the background or for fragments.
class Color
{
public:
  explicit Color(float = 0.156862745f, float = 0.156862745f, float = 0.156862745f, float = 1.0f); // Dark gray.
  [[maybe_unused]] Color(const Color &);

  void normalize();

  [[nodiscard]] float get_red() const;
  [[nodiscard]] float get_blue() const;
  [[nodiscard]] float get_green() const;
  [[nodiscard]] float get_alpha() const;

  [[maybe_unused]] void set_color(const Color &new_color);
  [[maybe_unused]] void set_color(float red, float blue, float green, float alpha);
  [[maybe_unused]] void clear();
  [[maybe_unused]] void print() const;

  Color &operator=(const Color &other_color);
  bool operator==(const Color &other_color);

private:
  float red = 0.0f;
  float green = 0.0f;
  float blue = 0.0f;
  float alpha = 0.0f;
};

#endif //OPENGL_DEV_COLOR_H
