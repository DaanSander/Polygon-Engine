
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
#include "entity\Entity.h"
#include "entity\behaviours\LightComponent.h"

//https://en.wikipedia.org/wiki/Rotation_matrix
//https://imdoingitwrong.wordpress.com/2011/01/31/light-attenuation/

int main() {
	using namespace engine;
	using namespace geometry;
	using namespace renderer;
	using namespace graphics;
	using namespace math;
	using namespace io;
	using namespace entity;

	Window* window = new Window(1080, 720, "Test");

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize glew" << std::endl;
		return -1;
	}

	SimpleRenderer* renderer = new SimpleRenderer();

	//Model* model = new Model("G:\\Projects\\C++\\Polygon-Engine\\Engine\\Engine\\res\\models\\Cube3.obj");
	Model* model = new Model("res\\models\\Cube3.obj");

	Shader* shader = new Shader(readFile("res\\shaders\\SimpleVertexShader.glsl"), readFile("res\\shaders\\SimpleFragmentShader.glsl"));
	graphics::Texture* texture = new graphics::Texture("G:\\Downloads\\container2_specular.png");

	Entity* entity = new Entity();

	LightComponent* component = new LightComponent();

	entity->addComponent(component);

	float x = 0.0f, y = 0.0f, z = 0.0f, pitch = 0.0f, yaw = 0.0f;

	Vector3f lightPos(0.0f, 0.0f, 1.0f);

	//Matrix4f orthographic = Matrix4f::orthographic(-2.0f, 2.0f, -1.0f, 1.0f, 0.0001f, 500.0f);
	Matrix4f perspective = Matrix4f::perspective((float)((float)window->getWidth() / (float)window->getHeight()), (float) DegToRad(70.0f), 0.1f, 1000.0f);

	shader->enable();
	glActiveTexture(GL_TEXTURE1);

	glUniform1i(shader->getUniformLocation("material.texture_specular1"), 1);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());

	glUniform3f(shader->getUniformLocation("objectColor"), 1.0f, 1.0f, 1.0f);
	glUniform3f(shader->getUniformLocation("lightColor"), 1.0f, 1.0f, 1.0f);

	glUniform3f(shader->getUniformLocation("material.diffuse"), 0.07568f, 0.61424f, 0.07568f);
	glUniform3f(shader->getUniformLocation("material.specular"), 0.5f, 0.5f, 0.5f);
	glUniform1f(shader->getUniformLocation("material.shininess"), 32.0f);
	//TODO verwijder light uniform loading het is namelijk verwijderd
	/*
	glUniform3f(shader->getUniformLocation("lights[0].ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(shader->getUniformLocation("lights[0].diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(shader->getUniformLocation("lights[0].specular"), 1.0f, 1.0f, 1.0f);

	glUniform1f(shader->getUniformLocation("lights[0].constant"), 1.0f);
	glUniform1f(shader->getUniformLocation("lights[0].linear"), 0.09f);
	glUniform1f(shader->getUniformLocation("lights[0].quadratic"), 0.032f);

	glUniform3f(shader->getUniformLocation("lights[0].direction"), 0.0f, 0.0f, -1.0f);
	glUniform1f(shader->getUniformLocation("lights[0].cutOff"), cos(DegToRad(12.5f)));
	
	*/
	shader->loadUniformMat4f(shader->getUniformLocation("projection"), perspective);
	while (!window->shouldClose()) {
		entity->position.x = lightPos.x;
		entity->position.y = lightPos.y;
		entity->position.z = lightPos.z;

		shader->loadLights(Light::getEffictiveLightsFor(Vector3f()));

		//glUniform3f(shader->getUniformLocation("lights[0].position"), lightPos.x, lightPos.y, lightPos.z);


		shader->loadUniformMat4f(shader->getUniformLocation("model"), (/*Matrix4f::rotation(Vector3f(z, x, y)) **/ Matrix4f::translation(Vector3f(0.0f, -4.0f, 0.0f))));
		shader->loadUniformMat4f(shader->getUniformLocation("view"), Matrix4f::translation(Vector3f(-x, -y, -z)) * Matrix4f::rotation(Vector3f(yaw, pitch)));
//		glUniform3f(shader->getUniformLocation("light.position"), lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(shader->getUniformLocation("light.position"), lightPos.x, lightPos.y, lightPos.z);

		glUniform3f(shader->getUniformLocation("viewPos"), x, y, z);
		glUniform3f(shader->getUniformLocation("viewRotation"), pitch, -yaw, 0.0f);

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
		if (window->getInputHandler()->keyDown(GLFW_KEY_UP))
			yaw -= 1.0f;
		if (window->getInputHandler()->keyDown(GLFW_KEY_DOWN))
			yaw += 1.0f;


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
		Entity::tickEntities();

		if (window->getInputHandler()->keyPressed(GLFW_KEY_F5)) {
			std::cout << "Reloading shader" << std::endl;
			shader->recompileShader(readFile("res\\shaders\\SimpleVertexShader.glsl"), readFile("res\\shaders\\SimpleFragmentShader.glsl"));
			glUniform3f(shader->getUniformLocation("objectColor"), 1.0f, 0.5f, 0.31f);
			glUniform3f(shader->getUniformLocation("lightColor"), 1.0f, 1.0f, 1.0f);

			glUniform3f(shader->getUniformLocation("material.diffuse"), 0.07568f, 0.61424f, 0.07568f);
			glUniform3f(shader->getUniformLocation("material.specular"), 0.5f, 0.5f, 0.5f);
			glUniform1f(shader->getUniformLocation("material.shininess"), 64.0f);

			glUniform3f(shader->getUniformLocation("light.ambient"), 0.2f, 0.2f, 0.2f);
			glUniform3f(shader->getUniformLocation("light.diffuse"), 0.5f, 0.5f, 0.5f);
			glUniform3f(shader->getUniformLocation("light.specular"), 1.0f, 1.0f, 1.0f);


			shader->loadUniformMat4f(shader->getUniformLocation("projection"), perspective);
		}

		if (window->getInputHandler()->keyDown(GLFW_KEY_ESCAPE))
			break;

		window->render();
	}
	shader->disable();

	graphics::Texture::deleteTextures();
	std::cout << "Deleted textures" << std::endl;
	delete model;
	delete entity;
	std::cout << "Deleted model" << std::endl;
	delete renderer;
	std::cout << "Deleted render" << std::endl;
	delete shader;
	std::cout << "Deleted shader" << std::endl;
	delete window;
	std::cout << "Deleted window" << std::endl;
}