#include "IndexBuffer.h"

namespace engine { namespace graphics {

		IndexBuffer::IndexBuffer(GLuint data[], GLsizei size) {
			this->size = size;
			glGenBuffers(1, &this->bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->bufferID);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1, &bufferID);
		}
}}