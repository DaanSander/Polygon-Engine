#pragma once

#include "../../geometry/Mesh.h"

namespace engine { namespace renderer {

		class SimpleRenderer {

		public:
			void prepareRenderer();

			void renderMesh(geometry::Mesh* mesh);

		};
}}