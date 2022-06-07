//
// Created by nami on 6/1/22.
//

#pragma once

#define MINIMUM_BUFFER_SIZE 255

class Vertex_buffer
{
public:
  Vertex_buffer();
  [[maybe_unused]] Vertex_buffer(const void *data, unsigned int size);

  static void set_sub_data(const void *data, unsigned int size);
  void bind() const;
  void unbind() const;
  void delete_buffer() const;
private:
  unsigned int m_renderer_id = 0;
};
