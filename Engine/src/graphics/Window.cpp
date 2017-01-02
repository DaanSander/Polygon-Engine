#include "Window.h"

namespace engine { namespace graphics {

	Window::Window(unsigned int width, unsigned int height, char* name) {
		this->width = width;
		this->height = height;
		this->name = name;

		if (!glfwInit()) {
			printf("Could not initialize the glfw library");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


		window = glfwCreateWindow(width, height, name, NULL, NULL);

		if (!window) {
			printf("Could not create window");
			glfwTerminate();
			return;
		}


		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		glfwShowWindow(window);
		glfwSetWindowUserPointer(window, this);

		this->inputHandler = new io::InputHandler(window);
	}

	Window::~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::render() {
		glfwSwapBuffers(window);
	}

	void Window::tick() {
		this->inputHandler->tick();
		glfwPollEvents();
	}

	int Window::shouldClose() {
		return glfwWindowShouldClose(window);
	}

}}