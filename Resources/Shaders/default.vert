#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 vertex_position;
//layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
uniform mat4 transform;

out vec2 texCoord0;

void main()
{
  gl_Position = transform * vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);
  texCoord0 = texCoord;
}