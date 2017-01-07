#include "Matrix4f.h"

namespace engine {
	namespace math {

		Matrix4f::Matrix4f() {
			for (int i = 0; i < 16; i++) {
				elements[i] = 0;
			}
		}

		Matrix4f::Matrix4f(float diagonal) {
			for (int i = 0; i < 16; i++) {
				elements[i] = 0;
			}
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Matrix4f Matrix4f::identity() {
			return Matrix4f(1.0f);
		}

		Matrix4f Matrix4f::multiply(const Matrix4f& other) const {
			Matrix4f out;
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					float o = 0;
					for (int c = 0; c < 4; c++) {
						o += this->elements[c + y * 4] * other.elements[x + c * 4];
					}
					out.elements[x + y * 4] = o;
				}
			}
			return out;
		}



		Matrix4f Matrix4f::perspective(float aspect, float fov, float near, float far) {
			Matrix4f out(1.0f);
			float tanHalf = tanh(fov / 2.0f);

			out.elements[0 + 0 * 4] = 1.0f / (tanHalf * aspect);
			out.elements[1 + 1 * 4] = 1.0f / tanHalf;
			out.elements[2 + 2 * 4] = -(far + near) / (far - near);
			out.elements[3 + 2 * 4] = -1.0f;
			out.elements[2 + 3 * 4] = -(2.0f * far * near) / (far - near);
			out.elements[3 + 3 * 4] = 0.0f;

			return out;
		}

		Matrix4f Matrix4f::orthographic(float left, float right, float bottom, float top, float near, float far) {
			Matrix4f out(1.0f);

			out.elements[0 + 0 * 4] = 2.0f / (right - left);
			out.elements[3 + 0 * 4] = -((right + left) / (right - left));

			out.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			out.elements[3 + 1 * 4] = -((top + bottom) / (top - bottom));

			out.elements[2 + 2 * 4] = -2.0f / (far - near);
			out.elements[3 + 2 * 4] = -((far + near) / (far - near));

			out.elements[3 + 3 * 4] = 1.0f;

			return out;
		}

		Matrix4f Matrix4f::rotation(const Vector3f& axis, float angle) {
			Matrix4f out(1.0f);
			float rad = (float)DegToRad(angle);
			float c = cos(rad);
			float s = sin(rad);
			float omc = 1 - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			out.elements[0 + 0 * 4] = c + x * omc;
			out.elements[1 + 0 * 4] = y * x * omc - z * s;
			out.elements[2 + 0 * 4] = x * z * omc - y * s;

			out.elements[0 + 1 * 4] = y * x * omc + z * s;
			out.elements[1 + 1 * 4] = c + y * omc;
			out.elements[2 + 1 * 4] = y * z * omc + x * s;

			out.elements[0 + 2 * 4] = z * x * omc + y * s;
			out.elements[1 + 2 * 4] = z * y * omc - x * s;
			out.elements[2 + 2 * 4] = c + z * omc;

			return out;
		}

		Matrix4f Matrix4f::rotation(const Vector3f& angles) {
			Matrix4f xRotation = rotation(Vector3f(1.0f, 0.0f, 0.0f), angles.x);
			Matrix4f yRotation = rotation(Vector3f(0.0f, 1.0f, 0.0f), angles.y);
			Matrix4f zRotation = rotation(Vector3f(0.0f, 0.0f, 1.0f), angles.z);
			return xRotation * yRotation * zRotation;
		}

		Matrix4f Matrix4f::scale(const Vector3f& scale) {
			Matrix4f out(1.0f);
			out.elements[0 + 0 * 4] = scale.x;
			out.elements[1 + 1 * 4] = scale.y;
			out.elements[2 + 2 * 4] = scale.z;
			return out;
		}

		Matrix4f Matrix4f::translation(const Vector3f& translation) {
			Matrix4f out(1.0f);
			out.elements[0 + 3 * 4] = translation.x;
			out.elements[1 + 3 * 4] = translation.y;
			out.elements[2 + 3 * 4] = translation.z;
			return out;
		}

		Matrix4f Matrix4f::lookAt(const Vector3f& object, const Vector3f& camera, const Vector3f& up) {
			Matrix4f out(1.0f);
			Vector3f zaxis = (object - camera).normalized();
			Vector3f xaxis = (up.cross(zaxis.normalized()));
			Vector3f yaxis = zaxis.cross(xaxis);

			out.elements[0 + 0 * 4] = xaxis.x;
			out.elements[1 + 0 * 4] = xaxis.y;
			out.elements[2 + 0 * 4] = xaxis.z;

			out.elements[0 + 1 * 4] = yaxis.x;
			out.elements[1 + 1 * 4] = yaxis.y;
			out.elements[2 + 1 * 4] = yaxis.z;

			out.elements[0 + 2 * 4] = -zaxis.x;
			out.elements[1 + 2 * 4] = -zaxis.y;
			out.elements[2 + 2 * 4] = -zaxis.z;

			return out * Matrix4f::translation(camera.reverse());
		}

		Matrix4f Matrix4f::transformation(const Matrix4f& rotation, const Matrix4f& scale, const Matrix4f& translation) {
			return (scale * rotation) * translation;
		}

		Matrix4f operator*(const Matrix4f &left, const Matrix4f &right) {
			return left.multiply(right);
		}

	}
}