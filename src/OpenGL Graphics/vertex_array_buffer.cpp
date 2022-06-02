//
// Created by nami on 6/1/22.
//

#include "renderer.h"
#include "vertex_array_buffer.h"

Vertex_array_buffer::Vertex_array_buffer()
{
  add_vao(&this->m_renderer_id);
}

void Vertex_array_buffer::bind() const
{
  bind_vao(&this->m_renderer_id);
}

void Vertex_array_buffer::unbind() const // NOLINT
{
  unbind_vao();
}

void Vertex_array_buffer::add_buffer(const Vertex_buffer &vbo, const Buffer_layout &layouts) const
{
  vbo.bind();
  const auto &elements = layouts.get_layouts();
  unsigned long offset = 0;
  for (unsigned int i = 0; i < elements.size(); i++)
  {
    const auto &element = elements[i];
    gl_call(glEnableVertexAttribArray(i));
    gl_call(glVertexAttribPointer(i, element.b_count, element.b_type,
                                  element.b_normalized, layouts.get_stride(),
                                  (const void *) offset));
    offset += element.b_count * vertex_buffer_layout_t::get_size_of_type(element.b_type);
    //  gl_call(glEnableVertexAttribArray(0));  // layout (location = 0) (position).
//  gl_call(glVertexAttribPointer(0, COUNT_VECTOR3D, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
//                                (void *) (POSITION_OFFSET)));
//
//  gl_call(glEnableVertexAttribArray(1));  // layout (location = 1) (color).
//  gl_call(glVertexAttribPointer(1, COUNT_COLOR, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
//                                (void *) (COLOR_OFFSET)));
//
//  gl_call(glEnableVertexAttribArray(2));  // layout (location = 2) (texCoord).
//  gl_call(glVertexAttribPointer(2, COUNT_VECTOR2D, GL_FLOAT, GL_FALSE, VERTEX_SIZE,
//                                (void *) (TEXTURE_OFFSET)));
  }
  vbo.unbind();
  unbind();
}

void Vertex_array_buffer::delete_array_buffer() const
{
  delete_vao(&this->m_renderer_id);
}
