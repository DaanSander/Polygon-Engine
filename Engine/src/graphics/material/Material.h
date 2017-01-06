#pragma once

#include "..\Shader.h"

namespace engine { namespace graphics {

	class Material {

		Shader* shader = nullptr;

	public:
		Material(Shader* shader);

		void enable();

		void disable();

		virtual void setupShader();

		inline Shader* getShader() { return shader; }
	};

}}