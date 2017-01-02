#include <iostream>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "graphics\Window.h"
#include "graphics\Shader.h"
#include "geometry\Mesh.h"
#include "graphics\renderer\SimpleRenderer.h"

//https://en.wikipedia.org/wiki/Rotation_matrix

char* vertexShader =
"#version 330 core \n" \
"layout (location = 0) in vec3 position; \n" \
"void main() { \n" \
"gl_Position = vec4(position.x, position.y, position.z, 1.0); \n" \
"}";

char* fragmentShader =
"#version 330 core \n" \
"out vec4 color; \n" \
"void main() { \n" \
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n" \
"}";

int main() {
	using namespace engine;
	using namespace graphics;
	using namespace geometry;
	using namespace renderer;

	Window* window = new Window(400, 600, "Test");

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize glew");
		return -1;
	}


	SimpleRenderer* renderer = new SimpleRenderer();

	Shader* shader = new Shader(vertexShader, fragmentShader);

	std::vector<GLfloat> vertices = { // First triangle
		0.5f,  0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f,  0.5f, 0.0f   // Top Left 
	};

	std::vector<GLuint> indices = {
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};

	Mesh* mesh = new Mesh(vertices);

	IndexBuffer* indexBuffer = new IndexBuffer(indices.data(), indices.size());

	mesh->getVertexArray()->setIndexBuffer(indexBuffer);

	shader->enable();
	while (!window->shouldClose()) {
		std::cout << window->getInputHandler()->buttonPressed(GLFW_MOUSE_BUTTON_1) << std::endl;
		renderer->prepareRenderer();
		renderer->renderMesh(mesh);
		window->tick();
		window->render();
	}
	shader->disable();

	delete mesh;
	delete window;
	delete renderer;
}