#pragma once

#include "Entity.h"

namespace engine {namespace entity {
	class Entity;

	struct EntityBehaviour {
		
		Entity* entity;

		~EntityBehaviour();

		virtual void init();

		virtual void tickBehaviour();
			
	};

}}