#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <GL\glew.h>
#include <assimp\scene.h>
#include "../math/Math.h"
#include "../graphics/Shader.h"

namespace engine { namespace geometry {

	struct Vertex {
		
		math::Vector3f position, normal;
		math::Vector2f uvCoord;
	};

	struct Texture {
		GLuint id;
		std::string type;
		aiString path;
	};

	class Mesh {

		GLuint VAO, VBO, EBO;

	public:
		std::vector<Vertex> vertices;
		std::vector<GLuint>  indices;
		std::vector<Texture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);

		~Mesh();

		void setupMesh();

		void setupTextures(graphics::Shader* shader);

		GLsizei getVertexCount() { return vertices.size(); };

		inline GLuint getVaoID() { return VAO; }

		inline GLuint getEboID() { return EBO; }
	};

}}