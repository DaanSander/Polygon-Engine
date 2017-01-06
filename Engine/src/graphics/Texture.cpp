#include "Texture.h"

namespace engine { namespace graphics {

	std::vector<Texture*>* Texture::textures = new std::vector<Texture*>(0);

	Texture::Texture(const char* path) {
		if (!exists(path)) {
			std::cout << "Could not find file " << path << std::endl;
			system("PAUSE");
			return;
		}

		FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path);
		if (format == FIF_UNKNOWN)
			format = FreeImage_GetFIFFromFilename(path);
		if (!FreeImage_FIFSupportsReading(format)) {
			std::cout << "Error file format is not supported" << std::endl;
			return;
		}

		FIBITMAP* bitMap = FreeImage_Load(format, path);

		const BYTE* pixels = FreeImage_GetBits(bitMap);

		unsigned int bpp = FreeImage_GetBPP(bitMap);
		GLsizei width = FreeImage_GetWidth(bitMap);
		GLsizei height = FreeImage_GetHeight(bitMap);
		GLsizei size = width * height * (bpp / 8);

		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);

		FreeImage_Unload(bitMap);

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		switch (bpp) {
		case 24:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, result);
			break;
		case 32:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, result);
			break;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		textures->push_back(this);
	}

	Texture::~Texture() {
		glDeleteTextures(1, &textureID);
	}

	void Texture::deleteTextures() {
		for (int i = 0; i < textures->size(); i++)
			delete textures->at(i);

		delete textures;
	}

}}