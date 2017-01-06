#include "Material.h"

namespace engine { namespace graphics {

	Material::Material(Shader* shader) : shader(shader) {

	}

	void Material::enable() {
		shader->enable();
	}

	void Material::disable() {
		shader->disable();
	}

	void Material::setupShader() {
		 
	}
}}