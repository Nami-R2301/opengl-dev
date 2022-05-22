#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 vertex_position;
//layout (location = 1) in vec4 color;
uniform float fragment_color;
uniform mat4 transform;

out vec4 color;

void main()
{
  gl_Position = transform * vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);
  color = vec4(fragment_color, fragment_color, clamp(fragment_color, 0.0, fragment_color), 1.0);
}