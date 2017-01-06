#include "Entity.h"

namespace engine { namespace entity {

	std::vector<Entity*>* Entity::entities;

	Entity::Entity(math::Vector3f position, math::Vector3f rotation, math::Vector3f scale, geometry::Mesh* mesh) {
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->mesh = mesh;

		entities->push_back(this);
	}

	void Entity::tick() {
		for (int i = 0; i < behaviours->size(); i++)
			behaviours->at(i)->tickBehaviour();
	}

	void Entity::addBehaviour(EntityBehaviour* behaviour) {
		behaviours->push_back(behaviour);
	}

	void Entity::deleteBehaviour(EntityBehaviour* behaviour) {
		for (int i = 0; i < behaviours->size(); i++) {
			if (typeid(behaviours->at(i)) == typeid(behaviour))
				behaviours->erase(behaviours->begin() + i);
		}
	}

	void Entity::tickEntities() {
		for (int i = 0; i < entities->size(); i++) {
			entities->at(i)->tick();
		}
	}

	math::Matrix4f Entity::getTransformation() {
		using namespace math;

		Matrix4f xRotation = Matrix4f::rotation(Vector3f(1.0f, 0.0f, 0.0f), rotation.x);
		Matrix4f yRotation = Matrix4f::rotation(Vector3f(0.0f, 1.0f, 0.0f), rotation.y);
		Matrix4f zRotation = Matrix4f::rotation(Vector3f(0.0f, 0.0f, 1.0f), rotation.z);

		Matrix4f rotation = (xRotation * yRotation) * zRotation;

		Matrix4f translation = Matrix4f::translation(position);
		Matrix4f scale = Matrix4f::scale(this->scale);

		return ((rotation * scale) * translation);
	}
}}