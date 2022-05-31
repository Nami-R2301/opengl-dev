#version 330 core

//in vec4 frag_color; // Imports the color from the Vertex Shader
in vec2 texCoord0;
uniform vec4 color;
uniform sampler2D sampler;
out vec4 fragColor;

void main()
{
  vec4 texture_color = texture(sampler, texCoord0.xy) * color;
  if (texture_color == 0) fragColor = color;
  else fragColor = texture_color;
}