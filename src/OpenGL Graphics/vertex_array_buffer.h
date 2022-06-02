//
// Created by nami on 6/1/22.
//

#ifndef OPENGL_DEV_VERTEX_ARRAY_BUFFER_H
#define OPENGL_DEV_VERTEX_ARRAY_BUFFER_H

#include "vertex_buffer.h"
#include "buffer_layout.h"

class Vertex_array_buffer
{
public:
  Vertex_array_buffer();

  void bind() const;
  void unbind() const;
  void add_buffer(const Vertex_buffer &vbo, const Buffer_layout &layouts) const;
  void delete_array_buffer() const;
private:
  unsigned int m_renderer_id = 0;
};

#endif //OPENGL_DEV_VERTEX_ARRAY_BUFFER_H
