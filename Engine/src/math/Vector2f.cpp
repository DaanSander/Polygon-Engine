#include "Vector2f.h"

namespace engine { namespace math {

	Vector2f::Vector2f(float x = 0.0f, float y = 0.0f) {
		this->x = x;
		this->y = y;
	}

	float Vector2f::magnitude() const {
		return sqrt((pow(this->x, 2.0f) + pow(this->y, 2.0f)));
	}

	float Vector2f::dot(Vector2f vector) const {
		return ((this->x * vector.x) + (this->x * vector.y) + (this->y * vector.x) + (this->y * vector.y));
	}

	Vector2f Vector2f::multiply(float scalar) const {
		Vector2f out;
		out.x = this->x * scalar;
		out.y = this->y * scalar;
		return out;
	}

	Vector2f Vector2f::reverse() const {
		Vector2f out;
		out.x = -this->x;
		out.y = -this->y;
		return out;
	}

	Vector2f Vector2f::substract(Vector2f other) const {
		return add(other.reverse());
	}

	Vector2f Vector2f::add(Vector2f other) const {
		Vector2f out;
		out = this->x + other.x;
		out = this->y + other.y;
		return out;
	}
}}