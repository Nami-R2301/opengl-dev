//
// Created by nami on 6/1/22.
//

#include "renderer.h"
#include "vertex_array_buffer.h"
#include "../Logs/logger.h"

Vertex_array_buffer::Vertex_array_buffer()
{
  alert(INFO, "CREATING VAO...");
  gl_call(glGenVertexArrays(1, &this->m_renderer_id));
}

void Vertex_array_buffer::bind() const
{
  gl_call(glBindVertexArray(this->m_renderer_id));
}

void Vertex_array_buffer::unbind() const // NOLINT
{
  gl_call(glBindVertexArray(0));
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
  }
  vbo.unbind();
  unbind();
}

void Vertex_array_buffer::delete_array_buffer() const
{
  gl_call(glDeleteVertexArrays(1, &this->m_renderer_id));
}
