#version 330 core
// Imports the color from the Vertex Shader
in vec4 color;
out vec4 FragColor;

void main()
{
  FragColor = color;
}