#include "SimpleRenderer.h"

namespace engine { namespace renderer {

	void SimpleRenderer::prepareRenderer() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
	}

	void SimpleRenderer::renderMesh(geometry::Mesh* mesh, graphics::Shader* shader) {
		GLuint errorCode = 0;
		mesh->setupTextures(shader);
		glBindVertexArray(mesh->getVaoID());

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getEboID());

		//glDrawArrays(GL_TRIANGLES, mesh->vertices.size() / (sizeof(math::Vector3f) + sizeof(math::Vector2f)), GL_FLOAT);
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
		if ((errorCode = glGetError()) != 0) {
			std::cout << "An error ocurred whilst trying to draw mesh elements error id: " << errorCode << std::endl;
			system("pause");
		}
		
		glBindVertexArray(0);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void SimpleRenderer::renderModel(geometry::Model* model, graphics::Shader* shader) {
		for (unsigned int i = 0; i < model->getMeshes().size(); i++)
			renderMesh(model->getMeshes()[i], shader);
	}
}}