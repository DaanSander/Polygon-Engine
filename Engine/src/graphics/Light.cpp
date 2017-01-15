#include "Light.h"

namespace engine { namespace graphics {

	std::vector<Light*> Light::lights;

	Light::Light(LightType type, math::Vector3f position, math::Vector3f color, float radius, float intensity) {
		this->position = position;
		this->color = color;
		this->radius = radius;
		this->intensity = intensity;

		lights.push_back(this);
	}

	float Light::getLinearFactor() {
		return 2.0f / radius;
	}

	float Light::getQuadraticFactor() {
		return 1.0f / (radius * radius);
	}

	std::vector<Light*> Light::getEffictiveLightsFor(math::Vector3f position) {
		std::vector<Light*> out;
		for (unsigned int i = 0; i < lights.size(); i++) {
			float length = (lights[i]->position - position).magnitude();
			if (pow(length, 0.5f) <= lights[i]->radius)
				out.push_back(lights[i]);
		}
		return out;
	}
}}