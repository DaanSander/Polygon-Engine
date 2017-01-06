#pragma once

#include "../../geometry/Model.h"

namespace engine { namespace renderer {

		class SimpleRenderer {

		public:
			void prepareRenderer();

			void renderMesh(geometry::Mesh* mesh);

			void renderModel(geometry::Model* model);

		};
}}