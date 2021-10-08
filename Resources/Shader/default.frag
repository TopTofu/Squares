#version 330 core

out vec4 frag_color;

in vec2 TexCoord;
in vec4 Color;

uniform sampler2D TexSampler;

void main()
{
	frag_color = Color;
}