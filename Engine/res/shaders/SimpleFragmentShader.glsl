#version 330 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
out vec4 color;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main() {
	float ambientFactor = 0.1f;
	vec3 ambient = lightColor * ambientFactor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(lightDir, Normal), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
	//color = vec4(texture(texture_diffuse1, TexCoords));
	color = vec4(result, 1.0);
}