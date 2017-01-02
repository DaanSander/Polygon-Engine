#pragma once

#include <vector>
#include <GL/glew.h>
#include "Buffer.h"
#include "IndexBuffer.h"

namespace engine { namespace graphics {

		class VertexArray {

			GLuint id;
			std::vector<Buffer*> buffers = std::vector<Buffer*>(0);
		public:
			IndexBuffer* indexBuffer = nullptr;

			VertexArray(IndexBuffer* indexBuffer);

			VertexArray(std::vector<Buffer*> buffers, IndexBuffer* indexBuffer);

			~VertexArray();

			void addBuffer(int index, Buffer* buffer);

			void addBuffer(Buffer* buffer);

			void setIndexBuffer(IndexBuffer* indexBuffer);

			inline GLuint getID() { return id; }
		};
}}