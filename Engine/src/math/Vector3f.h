#pragma once

#include <math.h>

namespace engine { namespace math {

	struct Vector3f {

		union {

			struct {
				float points[3];
			};

			struct {
				float x, y, z;
			};
		};

		Vector3f(float x, float y, float z);
		
		float magnitude() const;

		float dot(Vector3f other) const;

		Vector3f multiply(float scalar) const;

		Vector3f reverse() const;

		Vector3f substract(Vector3f other) const;

		Vector3f add(Vector3f other) const;
	};

}}