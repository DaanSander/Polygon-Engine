#pragma once

#include "../../geometry/Model.h"
#include "../../math/Math.h"

namespace engine { namespace renderer {

		class SimpleRenderer {

		public:
			void prepareRenderer();

			void renderMesh(geometry::Mesh* mesh, graphics::Shader* shader);

			void renderModel(geometry::Model* model, graphics::Shader* shader);
			
		};
}}