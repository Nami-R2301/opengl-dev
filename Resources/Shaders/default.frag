#version 330 core
// Imports the color from the Vertex Shader
in vec2 texCoord0;
uniform sampler2D sampler;
out vec4 fragColor;

void main()
{
  fragColor = texture(sampler, texCoord0.xy);
}