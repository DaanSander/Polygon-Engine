#pragma once

#include <iostream>
#include <vector>
#include <GLFW\glfw3.h>
#include "../io/InputHandler.h"

namespace engine {
	namespace io { class InputHandler; }
	namespace graphics {

	typedef void(*EventCallbackfunc)();

	class Window {

		unsigned int width, height;
		char* name;
		GLFWwindow* window;
		io::InputHandler* inputHandler = nullptr;

		std::vector<EventCallbackfunc> render_callbacks, update_callbacks, exit_callbacks;

	public:
		Window(unsigned int width, unsigned int height, char* name);

		~Window();

		void tick();

		void render();

		void addRenderCallback(EventCallbackfunc callback);

		void addUpdateCallback(EventCallbackfunc callback);

		void addExitCallback(EventCallbackfunc callback);

		void executeCallbacks(std::vector<EventCallbackfunc> callbacks);

		int shouldClose();

		inline unsigned int getWidth() { return width; }

		inline unsigned int getHeight() { return height; }

		inline io::InputHandler* getInputHandler() { return inputHandler; }
	};

}}