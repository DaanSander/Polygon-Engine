#pragma once

#include <string>
#include <vector>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "..\graphics\Texture.h"

namespace engine { namespace geometry {

	class Model {

		std::vector<Mesh*> meshes;
		std::string directory;

	public:
		Model(GLchar* path);

		~Model();

		inline std::vector<Mesh*> getMeshes() { return meshes; }
	private:
		void loadModel(std::string path);

		void processNode(aiNode* node, const aiScene* scene);

		Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName);
	};


}}