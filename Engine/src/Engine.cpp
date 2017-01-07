#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
"color = vec4(texture(texture_diffuse1, TexCoords)); \n" \
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

	Model* model = new Model("G:\\Projects\\C++\\Polygon-Engine\\Engine\\Engine\\res\\Nanosuit2\\nanosuit2.3ds");

	Shader* shader = new Shader(vertexShader, fragmentShader);

	float x = 0.0f, y = 0.0f, z = 0.0f;

	//Matrix4f orthographic = Matrix4f::orthographic(-2.0f, 2.0f, -1.0f, 1.0f, 0.0001f, 500.0f);
	Matrix4f perspective = Matrix4f::perspective((float) ((float) window->getWidth() / (float) window->getHeight()), 90.0f, 0.001f, 500.0f);

	shader->enable();
	shader->loadUniformMat4f(shader->getUniformLocation("projection"), perspective);
	while (!window->shouldClose()) {
		//std::cout << z << std::endl;
		//TODO rotatie uitesten
		shader->loadUniformMat4f(shader->getUniformLocation("model"), (Matrix4f::rotation(Vector3f(z, x, y)) * Matrix4f::translation(Vector3f(0.0f, -8.0f, 0.0f))));
		shader->loadUniformMat4f(shader->getUniformLocation("view"), Matrix4f::translation(Vector3f(0.0f, 0.0f, -10.0f)));

		renderer->prepareRenderer();

		renderer->renderModel(model, shader);

		window->tick();
		if (window->getInputHandler()->keyDown(GLFW_KEY_W))
			z += 1.0f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_S))
			z -= 1.0f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_D))
			x -= 1.0f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_A))
			x += 1.0f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_Q))
			y += 1.0f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_E))
			y -= 1.0f;

		if (window->getInputHandler()->keyDown(GLFW_KEY_ESCAPE))
			break;


		window->render();
	}
	shader->disable();
	
	graphics::Texture::deleteTextures();
	delete model;
	delete renderer;
	delete shader;
	delete window;
}