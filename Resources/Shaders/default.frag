#version 330 core

in vec4 frag_color;// Imports the color from the Vertex Shader
in vec2 texCoord0;// Texture coordinates.

uniform sampler2D sampler;

out vec4 fragColor;

void main()
{
  vec4 texture_color = texture(sampler, texCoord0.xy) * frag_color;
  if (texture_color == vec4(0.0)) fragColor = frag_color;
  else fragColor = texture_color * frag_color;
}