#version 330

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform sampler2D texture;

void main(void) {
	// flip y of texture
	vec2 flipped_texcoord = vec2(TexCoord.x, 1.0 - TexCoord.y);
	vec4 colorTexture = texture2D(texture, flipped_texcoord);

	// Ambient
	float ambientStrenght = 0.1f;
	vec3 ambient = ambientStrenght * lightColor;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	// Result
	vec4 result = (vec4(ambient, 1.0f) + vec4(diffuse, 1.0f) + vec4(specular, 1.0f)) * colorTexture;
	gl_FragColor = vec4(result);
}