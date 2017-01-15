#include "Entity.h"

namespace engine {
	namespace entity {

		std::vector<Entity*> Entity::entities(0);

		Entity::Entity(math::Vector3f position, math::Vector3f rotation, math::Vector3f scale) {
			this->position = position;
			this->rotation = rotation;
			this->scale = scale;

			entities.push_back(this);
		}

		Entity::~Entity() {
			for (unsigned int i = 0; i < behaviours.size(); i++)
				delete behaviours.at(i);

			//delete entities;
		}

		void Entity::tick() {
			for (unsigned int i = 0; i < behaviours.size(); i++)
				behaviours.at(i)->tickBehaviour();
		}

		void Entity::addComponent(EntityComponent* behaviour) {
			behaviours.push_back(behaviour);
			behaviour->entity = this;
			behaviour->init();
		}

		void Entity::deleteComponent(EntityComponent* behaviour) {
			for (unsigned int i = 0; i < behaviours.size(); i++) {
				if (typeid(behaviours.at(i)) == typeid(behaviour))
					behaviours.erase(behaviours.begin() + i);
			}
		}

		void Entity::tickEntities() {
			for (unsigned int i = 0; i < entities.size(); i++) {
				entities.at(i)->tick();
			}
		}

		template <class T>
		EntityComponent* Entity::getBehaviour() {
			for (int i = 0; i < behaviours->size(); i++) {
				if (std::is_base_of < T, behaviours->at(i))
					return behaviours->at(i);
			}
			return nullptr;
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