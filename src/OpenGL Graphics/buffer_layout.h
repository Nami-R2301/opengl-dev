//
// Created by nami on 6/2/22.
//

#ifndef OPENGL_DEV_BUFFER_LAYOUT_H
#define OPENGL_DEV_BUFFER_LAYOUT_H

#include <iostream>
#include <vector>
#include "renderer.h"
#include "../Math/vector_2f.h"
#include "../Math/vector_3f.h"

typedef struct vertex_buffer_layout_s
{
  unsigned int b_count;
  unsigned int b_type;
  unsigned char b_normalized;

  static unsigned int get_size_of_type(unsigned int type)
  {
    switch (type)
    {
      case VECTOR2F_SIZE:
        return VECTOR2F_SIZE;
      case VECTOR3F_SIZE:
        return VECTOR3F_SIZE;
      case COLOR_SIZE:
        return COLOR_SIZE;
      case GL_FLOAT:
        return 4;
      case GL_UNSIGNED_BYTE:
        return 1;
      case GL_UNSIGNED_INT:
        return 4;
      default:
        return 0;
    }
  }
} vertex_buffer_layout_t;

class Buffer_layout
{
public:
  inline Buffer_layout() : stride(0)
  {};

  template<typename T>
  void push([[maybe_unused]] unsigned int count_)
  {}

  [[nodiscard]] inline const std::vector<vertex_buffer_layout_t> &get_layouts() const
  { return this->layouts; };

  [[nodiscard]] inline unsigned int get_stride() const
  { return this->stride; };
private:
  std::vector<vertex_buffer_layout_t> layouts;
  unsigned int stride;
};

template<>
inline void Buffer_layout::push<float>(unsigned int count_)
{
  this->layouts.push_back({count_, GL_FLOAT, GL_FALSE});
  this->stride += count_ * vertex_buffer_layout_t::get_size_of_type(GL_FLOAT);
}

template<>
inline void Buffer_layout::push<unsigned int>(unsigned int count_)
{
  this->layouts.push_back({count_, GL_UNSIGNED_INT, GL_FALSE});
  this->stride += count_ * vertex_buffer_layout_t::get_size_of_type(GL_UNSIGNED_INT);
}

template<>
inline void Buffer_layout::push<unsigned char>(unsigned int count_)
{
  this->layouts.push_back({count_, GL_UNSIGNED_BYTE, GL_TRUE});
  this->stride += count_ * vertex_buffer_layout_t::get_size_of_type(GL_UNSIGNED_BYTE);
}

template<>
inline void Buffer_layout::push<Vector_2f>(unsigned int count_)
{
  this->layouts.push_back({(count_ * 2), GL_FLOAT, GL_FALSE});
  this->stride += count_ * vertex_buffer_layout_t::get_size_of_type(VECTOR2F_SIZE);
}

template<>
inline void Buffer_layout::push<Vector_3f>(unsigned int count_)
{
  this->layouts.push_back({(count_ * 3), GL_FLOAT, GL_FALSE});
  this->stride += count_ * vertex_buffer_layout_t::get_size_of_type(VECTOR3F_SIZE);
}

template<>
inline void Buffer_layout::push<Color>(unsigned int count_)
{
  this->layouts.push_back({(count_ * 4), GL_FLOAT, GL_FALSE});
  this->stride += count_ * vertex_buffer_layout_t::get_size_of_type(COLOR_SIZE);
}

#endif //OPENGL_DEV_BUFFER_LAYOUT_H
