#version 330 core

struct Material {
	sampler2D texture_diffuse1;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	//vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
out vec4 color;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform Material material;
uniform Light light;

void main() {
	vec3 fragColor = vec3(texture(material.texture_diffuse1, TexCoords).xyz);
	//vec3 fragColor = vec3(1.0f, 1.0f, 0.0f);
	
	float specularStrength = 0.5f;
	float ambientFactor = 0.1f;
	vec3 ambient = light.ambient * fragColor;

	vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(light.position - FragPos);
	vec3 lightDir = normalize(-light.direction);
	
	float diff = max(dot(lightDir, Normal), 0.0);
	vec3 diffuse = light.diffuse * diff * fragColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 reflectionDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(reflectionDir, viewDir), 0.0) , 285);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = (ambient + diffuse + specular) * objectColor;
	//color = vec4(texture(texture_diffuse1, TexCoords));
	color = vec4(result, 1.0);
}