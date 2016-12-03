#version 330

in vec2 TexCoord;

uniform sampler2D texture;

void main(void) {
	// flip y of texture
	vec2 flipped_texcoord = vec2(TexCoord.x, 1.0 - TexCoord.y);
	gl_FragColor = texture2D(texture, flipped_texcoord);
}