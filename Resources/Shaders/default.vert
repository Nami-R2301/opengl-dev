#version 460 core
// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec4 aColor;

// Outputs the color for the Fragment Shader
out vec4 color;
uniform float scale;

void main()
{
  gl_Position = vec4(size * aPos.x + aPos.x * scale, size * aPos.y + aPos.y * scale, size * aPos.z + aPos.z * scale, 1.0);
  // Assigns the colors from the Vertex Data to "color"
  color = aColor;
}