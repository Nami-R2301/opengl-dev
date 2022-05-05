#version 330 core
// Imports the color from the Vertex Shader
out vec4 FragColor;
uniform vec4 fragment_color;

void main()
{
  FragColor = fragment_color;
}