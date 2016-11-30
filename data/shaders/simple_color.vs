#version 330

attribute vec3 coord3d;

out vec3 f_color;

uniform vec3 v_color;
uniform mat4 mvp;

void main(void) {
	gl_Position = mvp * vec4(coord3d, 1.0);
	f_color = v_color;
}