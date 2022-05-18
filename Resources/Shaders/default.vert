#version 450 core
// Positions/Coordinates
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec4 color;

out vec4 fragment_color;
uniform float scale;
void main()
{
  gl_Position = vec4(vertex_position.x + (vertex_position.x * scale),
  vertex_position.y + (vertex_position.y * scale),
  vertex_position.z + (vertex_position.z * scale), 1.0);
  fragment_color = color;
}