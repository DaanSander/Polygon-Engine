#include "Vector4f.h"

namespace engine { namespace math {

	Vector4f::Vector4f(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float Vector4f::dot(Vector4f other) const {
		float xm = (this->x * other.x) + (this->x * other.y) + (this->x * other.z) + (this->x * other.w);
		float ym = (this->y * other.x) + (this->y * other.y) + (this->y * other.z) + (this->y * other.w);
		float zm = (this->z * other.x) + (this->z * other.y) + (this->z * other.z) + (this->z * other.w);
		float wm = (this->w * other.x) + (this->w * other.y) + (this->w * other.z) + (this->w * other.w);
		return xm + ym + zm + wm;
	}

	Vector4f Vector4f::multiply(float scalar) const {
		Vector4f out;
		out.x = this->x * scalar;
		out.y = this->y * scalar;
		out.z = this->z * scalar;
		out.w = this->w * scalar;
		return out;
	}

	Vector4f Vector4f::reverse() const {
		Vector4f out;
		out.x = -this->x;
		out.y = -this->y;
		out.z = -this->z;
		out.w = -this->w;
		return out;
	}

	Vector4f Vector4f::substract(Vector4f other) const {
		return add(reverse());
	}

	Vector4f Vector4f::add(Vector4f other) const {
		Vector4f out;
		out.x = this->x + other.x;
		out.y = this->y + other.y;
		out.z = this->z + other.z;
		out.w = this->w + other.w;
		return out;
	}

	Vector4f Vector4f::operator-() const {
		return this->reverse();
	}

	Vector4f operator-(const Vector4f& vector) {
		return vector.reverse();
	}

	Vector4f operator+(const Vector4f& a, const Vector4f& b) {
		return a.add(b);
	}

	Vector4f operator-(const Vector4f& a, const Vector4f& b) {
		return a.substract(b);
	}

	float operator* (const Vector4f& a, const Vector4f& other) {
		return a.dot(other);
	}

	Vector4f operator* (const Vector4f& vector, float scalar) {
		return vector.multiply(scalar);
	}
}}