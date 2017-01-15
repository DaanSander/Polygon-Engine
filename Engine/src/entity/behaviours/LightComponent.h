#pragma once

#include <vector>

#include "../EntityComponent.h"
#include "../../math/Math.h"
#include "../../graphics/Light.h"

namespace engine { namespace entity {

	class LightComponent : public EntityComponent {

	public:
		graphics::Light light = graphics::Light();

		virtual void tickBehaviour();
	};

}}