#pragma once

#include <GL/glew.h>

namespace engine { namespace graphics {

	class IndexBuffer {

		GLuint bufferID;
		GLsizei size;

	public:
		IndexBuffer(const GLvoid* data, GLsizei size);

		~IndexBuffer();

		inline GLuint getBufferID() { return bufferID; }

		inline GLsizei getSize() { return size; }
	};

}}