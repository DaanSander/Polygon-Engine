#pragma once

#include <math.h>

namespace engine { namespace math {

	struct Vector4f {

		union {

			struct {
				float points[4];
			};

			struct {
				float x, y, z, w;
			};
		};
		
		Vector4f(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

		float dot(Vector4f other) const;

		Vector4f multiply(float scalar) const;

		Vector4f reverse() const;

		Vector4f substract(Vector4f other) const;

		Vector4f add(Vector4f other) const;

		Vector4f operator-() const;

		friend Vector4f operator-(const Vector4f& vector);

		friend Vector4f operator+(const Vector4f& a, const Vector4f& b);

		friend Vector4f operator-(const Vector4f& a, const Vector4f& b);

		friend float operator* (const Vector4f& a, const Vector4f& other);

		friend Vector4f operator* (const Vector4f& vector, float scalar);
	};

}}