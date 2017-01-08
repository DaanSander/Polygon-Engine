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
		
		Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		
		float magnitude() const;

		float dot(Vector3f other) const;

		Vector3f normalized() const;

		Vector3f cross(Vector3f other) const;

		Vector3f multiply(float scalar) const;

		Vector3f reverse() const;

		Vector3f substract(Vector3f other) const;

		Vector3f add(Vector3f other) const;

		Vector3f operator-() const;

		friend Vector3f operator-(const Vector3f& vector);

		friend Vector3f operator+(const Vector3f& a, const Vector3f& b);

		friend Vector3f operator-(const Vector3f& a, const Vector3f& b);

		friend float operator* (const Vector3f& a, const Vector3f& other);

		friend Vector3f operator* (const Vector3f& vector, float scalar);
	};

}}