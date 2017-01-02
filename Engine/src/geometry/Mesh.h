#pragma once

#include <vector>
#include "../graphics/buffers/VertexArray.h"

namespace engine { namespace geometry {

	class Mesh {

		GLsizei vertexCount;
		graphics::VertexArray* vertexArray;

	public:
		Mesh(std::vector<GLfloat> vertices);

		~Mesh();

		inline graphics::VertexArray* getVertexArray() { return vertexArray; }

		inline GLsizei getVertexCount() { return vertexCount; };
	};

}}