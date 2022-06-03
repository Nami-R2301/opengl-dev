//
// Created by nami on 6/1/22.
//

#pragma once

class Index_buffer
{
public:
  Index_buffer() = default;
  Index_buffer(const unsigned int *data, unsigned int count);

  void bind() const;
  void unbind() const;
  void delete_buffer() const;

  [[nodiscard]] inline unsigned int get_count() const
  { return this->m_count; };
private:
  unsigned int m_renderer_id = 0;
  unsigned int m_count = 0;
};
