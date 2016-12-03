#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 view;
uniform mat4 model;

void main(void) {
	gl_Position = view * model * vec4(position, 1.0);
	TexCoord = texCoord;
}