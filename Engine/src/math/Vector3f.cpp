#include "Vector3f.h"

namespace engine { namespace math {

	Vector3f::Vector3f(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float Vector3f::magnitude() const {
		float length = (pow(this->x, 2.0f) + pow(this->y, 2.0f));
		return sqrt(pow(this->z, 2.0f) + length);
	}

	float Vector3f::dot(Vector3f other) const {
		float xm = (this->x * other.x) + (this->x * other.y) + (this->x * other.z);
		float ym = (this->y * other.x) + (this->y * other.y) + (this->y * other.z);
		float zm = (this->z * other.x) + (this->z * other.y) + (this->z * other.z);
		return xm + ym + zm;
	}

	Vector3f Vector3f::multiply(float scalar) const {
		Vector3f out;
		out.x = this->x * scalar;
		out.y = this->y * scalar;
		out.z = this->z * scalar;
		return out;
	}

	Vector3f Vector3f::reverse() const {
		Vector3f out;
		out.x = -this->x;
		out.y = -this->y;
		out.z = -this->z;
		return out;
	}

	Vector3f Vector3f::substract(Vector3f other) const {
		return add(other.reverse());
	}

	Vector3f Vector3f::add(Vector3f other) const {
		Vector3f out;
		out.x = this->x + other.x;
		out.y = this->y + other.y;
		out.z = this->z + other.z;
		return out;
	}
}}