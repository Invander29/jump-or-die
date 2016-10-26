#version 120

varying vec2 f_texcoord;

uniform float fade;
uniform sampler2D mUniTexture;

void main(void) {
	// flip y of texture
	vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
	gl_FragColor = texture2D(mUniTexture, flipped_texcoord);
}