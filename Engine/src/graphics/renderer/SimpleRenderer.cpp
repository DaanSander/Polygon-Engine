#include "SimpleRenderer.h"

namespace engine { namespace renderer {

	void SimpleRenderer::prepareRenderer() {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
	}

	void SimpleRenderer::renderMesh(geometry::Mesh* mesh) {
		if (mesh->getVertexArray()->indexBuffer == nullptr) {
			printf("Mesh does not contain an index buffer aborting \n");
			return;
		}
		glBindVertexArray(mesh->getVertexArray()->getID());
		glEnableVertexAttribArray(0);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getVertexArray()->indexBuffer->getBufferID());

		glDrawElements(GL_TRIANGLES, mesh->getVertexArray()->indexBuffer->getSize(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}}