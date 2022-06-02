//
// Created by nami on 6/1/22.
//

#include "index_buffer.h"

Index_buffer::Index_buffer(const unsigned int *data, unsigned int count) : m_count(count)
{
  add_ibo(&this->m_renderer_id);
  bind_ibo(&this->m_renderer_id);
  gl_call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void Index_buffer::bind() const
{
  bind_ibo(&this->m_renderer_id);
}

void Index_buffer::unbind() const  // NOLINT
{
  unbind_ibo();
}

void Index_buffer::delete_buffer() const
{
  delete_ibo(&this->m_renderer_id);
}
