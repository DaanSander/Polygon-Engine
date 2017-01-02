#pragma once

#include <math.h>

namespace engine { namespace math {

	struct Vector2f {

		union {

			struct {
				float points[2];
			};

			struct {
				float x, y;
			};

		};

		Vector2f(float x, float y);

		float magnitude() const;

		float dot(Vector2f other) const;

		Vector2f multiply(float scalar) const;

		Vector2f reverse() const;

		Vector2f substract(Vector2f other) const;

		Vector2f add(Vector2f other) const;
	};

}}