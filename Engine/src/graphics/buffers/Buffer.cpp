#include "Buffer.h"

namespace engine { namespace graphics {

	Buffer::Buffer(const GLvoid* data,GLuint dimensions, GLuint size) {
		this->dimensions = dimensions;
		glGenBuffers(1, &bufferID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(data) * dimensions * size, data, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer() {
		glDeleteBuffers(1, &bufferID);
	}

}}