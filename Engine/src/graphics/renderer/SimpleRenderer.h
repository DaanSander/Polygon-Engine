#pragma once

#include "../../geometry/Model.h"
#include "../../math/Math.h"

namespace engine { namespace renderer {

		class SimpleRenderer {

		public:
			void prepareRenderer();

			void renderMesh(geometry::Mesh* mesh);

			void renderModel(geometry::Model* model);

		};
}}