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
#include "io\FileUtils.h"

//https://en.wikipedia.org/wiki/Rotation_matrix

void tick();

int main() {
	using namespace engine;
	using namespace geometry;
	using namespace renderer;
	using namespace graphics;
	using namespace math;
	using namespace io;

	Window* window = new Window(1080, 720, "Test");

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize glew");
		return -1;
	}

	SimpleRenderer* renderer = new SimpleRenderer();

	Model* model = new Model("G:\\Projects\\C++\\Polygon-Engine\\Engine\\Engine\\res\\Nanosuit2\\nanosuit2.obj");

	Shader* shader = new Shader(readFile("res\\shaders\\SimpleVertexShader.glsl"), readFile("res\\shaders\\SimpleFragmentShader.glsl"));

	float x = 0.0f, y = 0.0f, z = 0.0f, pitch = 0.0f;
	
	Vector3f lightPos;

	//Matrix4f orthographic = Matrix4f::orthographic(-2.0f, 2.0f, -1.0f, 1.0f, 0.0001f, 500.0f);
	Matrix4f perspective = Matrix4f::perspective((float)((float) window->getWidth() / (float) window->getHeight()), DegToRad(70.0f), 0.1f, 1000.0f);

	shader->enable();
	glUniform3f(shader->getUniformLocation("objectColor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(shader->getUniformLocation("lightColor"), 1.0f, 1.0f, 1.0f);

	shader->loadUniformMat4f(shader->getUniformLocation("projection"), perspective);
	while (!window->shouldClose()) {
		//std::cout << window->getInputHandler()->getMousePosition().x << std::endl;
		//TODO rotatie uitesten
		shader->loadUniformMat4f(shader->getUniformLocation("model"), (/*Matrix4f::rotation(Vector3f(z, x, y)) **/ Matrix4f::translation(Vector3f(0.0f, -4.0f, 0.0f))));
		//shader->loadUniformMat4f(shader->getUniformLocation("view"), 
		//	((Matrix4f::rotation(Vector3f(0.0f, 1.0f), -window->getInputHandler()->getMousePosition().x)
		//		* Matrix4f::rotation(Vector3f(1.0f, 0.0f), -window->getInputHandler()->getMousePosition().y))* Matrix4f::translation(Vector3f(-x, -y, -z))));
		shader->loadUniformMat4f(shader->getUniformLocation("view"), Matrix4f::rotation(Vector3f(0.0f, pitch)) * Matrix4f::translation(Vector3f(-x, -y, -z)));
		glUniform3f(shader->getUniformLocation("lightPos"), lightPos.x, lightPos.y, lightPos.z);
		renderer->prepareRenderer();

		renderer->renderModel(model, shader);

		window->tick();
		if (window->getInputHandler()->keyDown(GLFW_KEY_W))
			z -= 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_S))
			z += 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_D))
			x += 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_A))
			x -= 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_Q))
			y += 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_E))
			y -= 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_RIGHT))
			pitch += 1.0f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_LEFT))
			pitch -= 1.0f;

		if (window->getInputHandler()->keyDown(GLFW_KEY_KP_8))
			lightPos.z -= 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_KP_2))
			lightPos.z += 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_KP_4))
			lightPos.x += 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_KP_6))
			lightPos.x -= 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_KP_7))
			lightPos.y += 0.2f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_KP_9))
			lightPos.y -= 0.2f;

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