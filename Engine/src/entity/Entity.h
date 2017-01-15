#pragma once

#include <typeinfo>
#include <vector>
#include "EntityComponent.h"
#include "..\math\Math.h"
#include "..\geometry\Mesh.h"

namespace engine { namespace entity {

	struct EntityComponent;

		class Entity {

			static std::vector<Entity*> entities;
			std::vector<EntityComponent*> behaviours;
			//geometry::Mesh* mesh;

		public:
			math::Vector3f position, rotation, scale;

			Entity(math::Vector3f position = math::Vector3f(), math::Vector3f rotation = math::Vector3f(), math::Vector3f scale = math::Vector3f());

			~Entity();

			void tick();

			void addComponent(EntityComponent* behaviour);

			void deleteComponent(EntityComponent* behaviour);

			template <class T>
			EntityComponent* getBehaviour();

			math::Matrix4f getTransformation();
			
			static void tickEntities();

			static inline std::vector<Entity*> getEntities() { return entities; }
		};
}}