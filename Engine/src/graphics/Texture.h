#pragma once

#include <vector>
#include <iostream>
#include <FreeImage.h>
#include <GL\glew.h>

namespace engine { namespace graphics {

	class Texture {

		static std::vector<Texture*>* textures;

		GLuint textureID;
		
		inline static bool exists(const char* path) {
			struct stat buffer;
			return (stat(path, &buffer) == 0);
		}

	public:

		Texture(const char* path);

		~Texture();

		static void deleteTextures();
		
		inline GLuint getTextureID() { return textureID; }
	};

}}