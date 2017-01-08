#pragma once

#include <GL/glew.h>

namespace engine {namespace graphics {

	class Buffer {

		GLuint bufferID, dimensions;

	public:
		Buffer(const GLvoid* data,GLuint dimensions, GLuint size);

		~Buffer();

		inline GLuint getDimensions() { return dimensions; }

		inline GLuint getBufferID() { return bufferID; }

	};

}}