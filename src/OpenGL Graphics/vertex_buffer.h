//
// Created by nami on 6/1/22.
//

#ifndef OPENGL_DEV_VERTEX_BUFFER_H
#define OPENGL_DEV_VERTEX_BUFFER_H

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

#endif //OPENGL_DEV_VERTEX_BUFFER_H
