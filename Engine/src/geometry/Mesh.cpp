#include "Mesh.h"

namespace engine { namespace geometry {

		Mesh::Mesh(std::vector<GLfloat> vertices) {
			this->vertexCount = vertices.size() / 3;
			using namespace graphics;
			vertexArray = new VertexArray(nullptr);
			Buffer* buffer = new Buffer(vertices.data(), 3, vertices.size());

			vertexArray->addBuffer(buffer);
		}

		Mesh::~Mesh() {
			delete vertexArray;
		}

}}