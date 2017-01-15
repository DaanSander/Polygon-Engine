#pragma once

#include <vector>
#include "../math/Math.h"

namespace engine { namespace graphics {

	enum LightType {
		POINT,
		SPOT,
		DIRECTIONAL
	};

	struct Light {
		//TODO direction toevoegen
		static std::vector<Light*> lights;

		float radius, intensity;

		LightType type;
		math::Vector3f position;
		math::Vector3f color;

		Light(LightType type = POINT, math::Vector3f position = math::Vector3f(1.0f), math::Vector3f color = math::Vector3f(1.0f, 1.0f, 1.0f),
			float radius = 5.0f, float intensity = 1.0f);

		float getLinearFactor();

		float getQuadraticFactor();

		static std::vector<Light*> getEffictiveLightsFor(math::Vector3f position);


	};

}}