#pragma once

#include "../math/Math.h"
#include "../graphics/Window.h"

#define MAX_KEYS 1024
#define MAX_BUTTONS 5

namespace engine { namespace io {

	class InputHandler {

		GLFWwindow* window;
		double x, y;
		math::Vector2f mousePosition;

	public:
		bool keys_down[MAX_KEYS],
			 keys_pressed[MAX_KEYS],
			 buttons_down[MAX_KEYS],
			 buttons_pressed[MAX_BUTTONS];

		InputHandler(GLFWwindow* window);

		void tick();

		inline bool keyDown(unsigned int key) { return keys_down[key]; }

		inline bool keyPressed(unsigned int key) { return keys_pressed[key]; }

		inline bool buttonDown(unsigned int button) { return buttons_down[button]; }
	
		inline bool buttonPressed(unsigned int button) { return buttons_pressed[button]; }

		inline GLFWwindow* getWindow() { return window; }

		inline math::Vector2f getMousePosition() { return mousePosition; }
	};

}}