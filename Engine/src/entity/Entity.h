#pragma once

#include <typeinfo>
#include <vector>
#include "EntityBehaviour.h"
#include "..\math\Math.h"
#include "..\geometry\Mesh.h"

namespace engine { namespace entity {

	struct EntityBehaviour;

		class Entity {

			static std::vector<Entity*>* entities;
			std::vector<EntityBehaviour*>* behaviours;
			geometry::Mesh* mesh;

		public:
			math::Vector3f position, rotation, scale;

			Entity(math::Vector3f position = math::Vector3f(), math::Vector3f rotation = math::Vector3f(), math::Vector3f scale = math::Vector3f(),
				geometry::Mesh* mesh = nullptr);

			~Entity();

			void tick();

			void addBehaviour(EntityBehaviour* behaviour);

			void deleteBehaviour(EntityBehaviour* behaviour);

			template <class T>
			EntityBehaviour* getBehaviour();

			math::Matrix4f getTransformation();
			
			static void tickEntities();

			static inline std::vector<Entity*>* getEntities() { return entities; }
		};
}}