#include "VertexArray.h"

namespace engine { namespace graphics {

		VertexArray::VertexArray(IndexBuffer* indexBuffer = nullptr) {
			this->indexBuffer = indexBuffer;
			glGenVertexArrays(1, &this->id);
		}

		VertexArray::VertexArray(std::vector<Buffer*> buffers, IndexBuffer* indexBuffer = nullptr) {
			this->indexBuffer = indexBuffer;
			glGenVertexArrays(1, &this->id);
			glBindVertexArray(this->id);

			for (unsigned int i = 0; i < buffers.size(); i++)
				addBuffer(i, buffers[i]);

			glBindVertexArray(0);
		}

		VertexArray::~VertexArray() {
			for (unsigned int i = 0; i < buffers.size(); i++) {
				delete buffers[i];
			}

			indexBuffer->~IndexBuffer();

			glDeleteVertexArrays(1, &this->id);
		}

		void VertexArray::addBuffer(int index, Buffer* buffer) {
			if (index > 15) {
				printf("Exceeding maximum amount for stored buffers");
				return;
			}
			if (buffers[index] != NULL) {
				printf("WARNING VertexArray: %u already has a buffer at index: %u ! Overwriting already existing one", this->id, index);
			}
			glBindVertexArray(this->id);
			glBindBuffer(GL_ARRAY_BUFFER, buffer->getBufferID());

			glVertexAttribPointer(index, buffer->getDimensions(), GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		void VertexArray::addBuffer(Buffer* buffer) {
			if (buffers.size() + 1 > 15)
				printf("The VertexArray: %u is full", this->id);

			glBindVertexArray(this->id);
			glBindBuffer(GL_ARRAY_BUFFER, buffer->getBufferID());

			//TODO check if the index is right
			glVertexAttribPointer(buffers.size(), buffer->getDimensions(), GL_FLOAT, GL_FALSE, 0, 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		
		void VertexArray::setIndexBuffer(IndexBuffer* indexBuffer) {
			this->indexBuffer = indexBuffer;
			glBindVertexArray(this->id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->getBufferID());

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
}}