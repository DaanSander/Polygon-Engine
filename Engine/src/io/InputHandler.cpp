#include "InputHandler.h"

namespace engine { namespace io {

	void key_callback(GLFWwindow* windowptr, int key, int scancode, int action, int mods);
	void button_callback(GLFWwindow* windowptr, int button, int action, int mods);

	InputHandler::InputHandler(GLFWwindow* window) {
		this->window = window;

		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, button_callback);
	}

	void key_callback(GLFWwindow* windowptr, int key, int scancode, int action, int mods) {
		if (key > MAX_KEYS) return;
		using namespace graphics;
		Window* window = (Window *)glfwGetWindowUserPointer(windowptr);
		InputHandler* inputHandler = window->getInputHandler();

		switch (action) {
		case GLFW_PRESS:
			if (inputHandler->keyDown(key)) return;
			inputHandler->keys_down[key] = true;
			inputHandler->keys_pressed[key] = true;
			break;
		case GLFW_RELEASE:
			inputHandler->keys_down[key] = false;
			inputHandler->keys_pressed[key] = false;
			break;
		}
	}

	void button_callback(GLFWwindow* windowptr, int button, int action, int mods) {
		if (button > MAX_BUTTONS) return;
		using namespace graphics;
		Window* window = (Window *)glfwGetWindowUserPointer(windowptr);
		InputHandler* inputHandler = window->getInputHandler();

		switch (action) {
		case GLFW_PRESS:
			if (inputHandler->buttons_down[button]) break;
			inputHandler->buttons_down[button] = true;
			inputHandler->buttons_pressed[button] = true;
			break;
		case GLFW_RELEASE:
			inputHandler->buttons_down[button] = false;
			inputHandler->buttons_pressed[button] = false;
			break;
		}
	}

	void InputHandler::tick() {
		memset(this->keys_pressed, 0, MAX_KEYS);
		memset(this->buttons_pressed, 0, MAX_BUTTONS);

		glfwGetCursorPos(window, &this->x, &this->y);
		mousePosition.x = (float)x;
		mousePosition.y = (float)y;
	}
}}