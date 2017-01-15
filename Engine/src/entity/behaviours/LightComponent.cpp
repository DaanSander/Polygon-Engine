#include "LightComponent.h"

namespace engine { namespace entity {

	void LightComponent::tickBehaviour() {
			light.position = entity->position;
	}

}}