//
// Created by nami on 6/1/22.
//

#include "index_buffer.h"
#include "../Logs/logger.h"
#include "renderer.h"

Index_buffer::Index_buffer(const unsigned int *data, unsigned int count) : m_count(count)
{
  alert(INFO, "CREATING EVO...");
  gl_call(glGenBuffers(1, &this->m_renderer_id));
  bind();
  gl_call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void Index_buffer::bind() const
{
  alert(INFO, "BINDING EVO...");
  gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_renderer_id));
}

void Index_buffer::unbind() const  // NOLINT
{
  gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void Index_buffer::delete_buffer() const
{
  gl_call(glDeleteBuffers(1, &this->m_renderer_id));
}
