//
// Created by nami on 6/1/22.
//

#include "renderer.h"
#include "vertex_buffer.h"

Vertex_buffer::Vertex_buffer(const void *data, unsigned int size)
{
  add_vbo(&this->m_renderer_id);
  bind_vbo(&this->m_renderer_id);
  gl_call(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void Vertex_buffer::bind() const
{
  bind_vbo(&this->m_renderer_id);
}

void Vertex_buffer::unbind() const // NOLINT
{
  unbind_vbo();
}

void Vertex_buffer::delete_buffer() const
{
  delete_vbo(&this->m_renderer_id);
}
