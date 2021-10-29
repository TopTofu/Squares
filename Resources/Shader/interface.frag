#version 330 core

out vec4 frag_color;

in vec2 TexCoord;
in vec4 Color;

uniform sampler2D TexSampler;
uniform int Textured;

void main()
{
	// uses texSampler only if Textured == 1
	frag_color =  Textured  * texture(TexSampler, TexCoord) - (Textured - 1) * Color;
}