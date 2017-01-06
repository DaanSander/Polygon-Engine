#include "SimpleRenderer.h"

namespace engine { namespace renderer {

	void SimpleRenderer::prepareRenderer() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
	}

	void SimpleRenderer::renderMesh(geometry::Mesh* mesh) {
		mesh->setupMesh();
		glBindVertexArray(mesh->getVaoID());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getVertexArray()->indexBuffer->getBufferID());

		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void SimpleRenderer::renderModel(geometry::Model* model) {
		for (int i = 0; i < model->getMeshes().size(); i++)
			renderMesh(&model->getMeshes()[i]);
	}
}}