#pragma once

#include <iostream>
#include <GLFW\glfw3.h>
#include "../io/InputHandler.h"

namespace engine {
	namespace io { class InputHandler; }
	namespace graphics {

	typedef void(*EventCallbackfunc);

	class Window {

		unsigned int width, height;
		char* name;
		GLFWwindow* window;
		io::InputHandler* inputHandler = nullptr;

	public:
		Window(unsigned int width, unsigned int height, char* name);

		~Window();

		void tick();

		void render();

		int shouldClose();

		inline unsigned int getWidth() { return width; }

		inline unsigned int getHeight() { return height; }

		inline io::InputHandler* getInputHandler() { return inputHandler; }
	};

}}