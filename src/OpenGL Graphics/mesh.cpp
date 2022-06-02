//
// Created by nami on 5/14/22.
//

#include "mesh.h"
#include "buffer_layout.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "res_loader.h"
#include "renderer.h"

void Mesh::setup_mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
                      const Buffer_layout &layout)
{
  this->vbo = Vertex_buffer(vertices.data(), VERTEX_SIZE * vertices.size());
  this->vao.bind();
  this->ibo = Index_buffer(indices.data(), indices.size());
  this->tex = Texture(load_texture_file("../Resources/Textures/tiles.png"));
  this->vao.add_buffer(this->vbo, layout);

  this->tex.unbind();
  this->vao.unbind();
  this->vbo.unbind();
  this->ibo.unbind();
}

void Mesh::draw()
{
  this->vao.bind();
  this->tex.bind(0);

  // Draw from vertex_source arrays.
  gl_call(glDrawElements(GL_TRIANGLES, this->ibo.get_count(), GL_UNSIGNED_INT, nullptr));
}

void Mesh::delete_buffers() const
{
  alert(INFO, "DELETING VBO...");
  this->vbo.delete_buffer();
  alert(INFO, "DELETING VAO...");
  this->vao.delete_array_buffer();
  alert(INFO, "DELETING IBO...");
  this->ibo.delete_buffer();
  alert(INFO, "DELETING TEXTURE...");
  this->tex.delete_texture();
}
