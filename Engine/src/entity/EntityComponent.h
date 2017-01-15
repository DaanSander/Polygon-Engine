#pragma once

#include "Entity.h"

namespace engine {namespace entity {
	class Entity;

	struct EntityComponent {
		
		Entity* entity;

		~EntityComponent();

		virtual void init();

		virtual void tickBehaviour();
			
	};

}}