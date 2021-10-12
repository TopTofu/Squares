#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec3 aNormal;

uniform mat4 transform;
uniform mat4 camera;

out vec3 FragPos;
out vec2 TexCoord;
out vec4 Color;
out vec3 Normal;

void main()
{
	gl_Position = camera * transform * vec4(aPos, 1.0f);	
	
	FragPos = vec3(transform * vec4(aPos, 1.0));
	TexCoord = aTexCoord;
	Color = aColor;
	Normal = normalize(vec3(transform * vec4(aNormal, 0.0)));
}