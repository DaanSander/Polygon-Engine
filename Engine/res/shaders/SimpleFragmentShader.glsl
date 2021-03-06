#version 330 core

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	//vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;

	float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in mat4 viewMat;
out vec4 color;

uniform vec3 viewPos;
uniform vec3 viewRotation;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

uniform Material material;

uniform Light lights[4];

//uniform Light light;

void main() {

	vec3 lightDir = normalize(lights[0].position - FragPos);
	float theta = dot(lightDir, normalize(-lights[0].direction));

	//if(theta > lights[0].cutOff) {
	//vec3 fragColor = vec3(1.0f, 1.0f, 0.0f);
	float distance = length(lights[0].position - FragPos);
	float attenuation = 1.0f / (lights[0].constant + lights[0].linear * distance + lights[0].quadratic * (distance * distance));
	
	vec3 fragColor = vec3(texture(material.texture_diffuse1, TexCoords).xyz);

	vec3 ambient = lights[0].ambient * fragColor;
	vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(-lights[0].direction);
	
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = (lights[0].diffuse * diff * fragColor);

	//Right light without rotation of view
	//vec3 viewDir = normalize(viewPos - FragPos);

	//Incorrect close highlight with correct rotation of view
	//vec3 viewDir = normalize(FragPos - (viewRotation - viewPos));

	//Possibly right higlight at close and rotation of view
	vec3 viewDir = normalize((viewPos + viewRotation) - FragPos);
	
	vec3 reflectionDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectionDir), 0.0) , material.shininess);
	vec3 specular = (lights[0].specular * spec * vec3(texture(material.texture_specular1, TexCoords)));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular);
	//color = vec4(texture(texture_diffuse1, TexCoords));
	color = vec4(result, 1.0);
	//} else
		//color = vec4(lights[0].ambient * vec3(texture(material.texture_diffuse1, TexCoords)), 1.0f);
}