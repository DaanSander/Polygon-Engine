#pragma once

#include "Mathf.h"
#include "Vector3f.h"

namespace engine {
	namespace math {

		struct Matrix4f {

			float elements[4 * 4];

			Matrix4f();

			Matrix4f(float diagonal);

			static Matrix4f identity();

			Matrix4f multiply(const Matrix4f& other) const;

			static Matrix4f perspective(float aspect, float fov, float near, float far);

			//static Matrix4f perspective(float aspectHonW, float fovYRadians, float near, float far);

			static Matrix4f orthographic(float left, float right, float bottom, float top, float near, float far);

			static Matrix4f rotation(const Vector3f& axis, float degrees);
			
			static Matrix4f rotation(const Vector3f& angles);

			static Matrix4f scale(const Vector3f& scale);

			static Matrix4f translation(const Vector3f& translation);

			static Matrix4f transformation(const Matrix4f& rotation, const Matrix4f& scale, const Matrix4f& translation);

			static Matrix4f lookAt(const Vector3f& object, const Vector3f& camera, const Vector3f& up);

			friend Matrix4f operator*(const Matrix4f& left, const Matrix4f& right);
		};

	}
}