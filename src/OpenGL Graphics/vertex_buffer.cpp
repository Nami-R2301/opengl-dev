//
// Created by nami on 6/1/22.
//

#include "renderer.h"
#include "vertex_buffer.h"
#include "../Logs/logger.h"

Vertex_buffer::Vertex_buffer()
{
  alert(INFO, "CREATING VBO...");
  gl_call(glGenBuffers(1, &this->m_renderer_id)); // Create empty buffer for our vertex_source data.
  bind();
  gl_call(glBufferData(GL_ARRAY_BUFFER, VERTEX_SIZE * MINIMUM_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW));
}

[[maybe_unused]] Vertex_buffer::Vertex_buffer(const void *data, unsigned int size)
{
  alert(INFO, "CREATING VBO...");
  gl_call(glGenBuffers(1, &this->m_renderer_id)); // Create empty buffer for our vertex_source data.
  bind();
  gl_call(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void Vertex_buffer::set_sub_data(const void *data, unsigned int size)
{
  gl_call(glBufferSubData(GL_ARRAY_BUFFER, 0, VERTEX_SIZE * size, data));
}

void Vertex_buffer::bind() const
{
//  alert(INFO, "BINDING VBO...");  Removed due to spam.
  gl_call(glBindBuffer(GL_ARRAY_BUFFER, this->m_renderer_id));
}

void Vertex_buffer::unbind() const // NOLINT
{
  gl_call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Vertex_buffer::delete_buffer() const
{
  gl_call(glDeleteBuffers(1, &this->m_renderer_id));
}
