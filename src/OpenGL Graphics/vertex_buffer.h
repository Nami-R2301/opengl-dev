//
// Created by nami on 6/1/22.
//

#pragma once

class Vertex_buffer
{
public:
  Vertex_buffer() = default;
  Vertex_buffer(const void *data, unsigned int size);

  void bind() const;
  void unbind() const;
  void delete_buffer() const;
private:
  unsigned int m_renderer_id = 0;
};
