#pragma once

#include "../EntityComponent.h"
#include "../../geometry/Model.h"

namespace engine { namespace entity {

	struct ModelRenderComponent : public EntityComponent {

		geometry::Model* model;

	};

}}