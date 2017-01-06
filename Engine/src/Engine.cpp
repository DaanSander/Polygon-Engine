#include <iostream>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <assimp\ai_assert.h>
#include "geometry\Model.h"
#include "graphics\Window.h"
#include "graphics\renderer\SimpleRenderer.h"

//https://en.wikipedia.org/wiki/Rotation_matrix

char* vertexShader =
"#version 330 core \n" \
"layout (location = 0) in vec3 position; \n" \
"layout (location = 1) in vec3 normal; \n" \
"layout (location = 2) in vec2 texCoords;\n" \
"out vec2 TexCoords \n;" \
"uniform mat4 model; \n" \
"uniform mat4 view; \n" \
"uniform mat4 projection; \n" \
"void main() { \n" \
"gl_Position = projection * view * model * vec4(position, 1.0f); \n" \
"TexCoords = texCoords;" \
"}";

char* fragmentShader =
"#version 330 core \n" \
"in vec2 TexCoords; \n" \
"out vec4 color; \n" \
"uniform sampler2D texture_diffuse1; \n" \
"void main() { \n" \
"color = vec4(1.0f, 1.0f, 0.0f, 1.0f); \n" \
"}";

int main() {
	using namespace engine;
	using namespace geometry;
	using namespace renderer;
	using namespace graphics;
	using namespace math;

	Window* window = new Window(800, 600, "Test");

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize glew");
		return -1;
	}

	SimpleRenderer* renderer = new SimpleRenderer();

	Model* model = new Model("G:\\Projects\\C++\\Polygon-Engine\\Engine\\Engine\\res\\Sphere2.obj");

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
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Matrix4f perspective = Matrix4f::perspective((float) ((float) window->getWidth() / (float) window->getHeight()), 90.0f, 0.001f, 500.0f);
	
	shader->enable();
	while (!window->shouldClose()) {
		//std::cout << z << std::endl;
		shader->loadUniformMat4f(shader->getUniformLocation("model"), Matrix4f::identity());
		shader->loadUniformMat4f(shader->getUniformLocation("view"), Matrix4f::translation(Vector3f(x, y, z)));
		shader->loadUniformMat4f(shader->getUniformLocation("projection"), Matrix4f::identity());

		renderer->prepareRenderer();

		renderer->renderModel(model);

		window->tick();
		if (window->getInputHandler()->keyDown(GLFW_KEY_W))
			z += 0.1f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_S))
			z -= 0.1f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_D))
			x -= 0.1f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_A))
			x += 0.1f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_Q))
			y += 0.1f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_E))
			y -= 0.1f;

		if (window->getInputHandler()->keyDown(GLFW_KEY_ESCAPE))
			break;


		window->render();
	}
	shader->disable();

	graphics::Texture::deleteTextures();
	delete model;
	delete renderer;
	delete window;
}