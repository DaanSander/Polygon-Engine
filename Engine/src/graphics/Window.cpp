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
		glEnable(GL_DEPTH_TEST); 
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

	}

	Window::~Window() {
		delete inputHandler;
		glfwTerminate();
		//glfwDestroyWindow(window);
	}

	void Window::executeCallbacks(std::vector<EventCallbackfunc> callbacks) {
		for (unsigned int i = 0; i < callbacks.size(); i++) {
			callbacks[i]();
		}
	}

	void Window::addRenderCallback(EventCallbackfunc callback) {
		render_callbacks.push_back(callback);
	}
	
	void Window::addUpdateCallback(EventCallbackfunc callback) {
		update_callbacks.push_back(callback);
	}
	
	void Window::addExitCallback(EventCallbackfunc callback) {
		exit_callbacks.push_back(callback);
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