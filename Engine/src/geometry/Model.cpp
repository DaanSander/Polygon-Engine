#include "Model.h"

namespace engine {
	namespace geometry {

		Model::Model(GLchar* path) {
			this->loadModel(path);
		}

		void Model::loadModel(std::string path) {
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
				std::cout << "An error ocurred while loading model at path: " << path << " log: " << importer.GetErrorString() << std::endl;
				return;
			}
			this->directory = path.substr(0, path.find_last_of("/"));

			this->processNode(scene->mRootNode, scene);
		}

		void Model::processNode(aiNode* node, const aiScene* scene) {
			for (int i = 0; i < node->mNumMeshes; i++) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				if (mesh == nullptr) {
					std::cout << "MESH IS NULL" << std::endl;
					system("pause");
				}
				Mesh gMesh = this->processMesh(mesh, scene);
				meshes.push_back(gMesh);
			}

			for (int i = 0; i < node->mNumChildren; i++) {
				if (node->mChildren[i] == nullptr) {
					std::cout << "NODE IS NULL" << std::endl;
					system("pause");
				}
				processNode(node->mChildren[i], scene);
			}
		}

		Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
			using namespace math;
			using namespace std;
			vector<Vertex*> vertices;
			vector<GLuint> indices;
			vector<Texture> textures;

			for (int i = 0; i < mesh->mNumVertices; i++) {
				Vertex vertex;

				Vector3f vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;

				vertex.position = vector;
				
				Vector3f normal;
				normal.x = mesh->mNormals[i].x;
				normal.y = mesh->mNormals[i].y;
				normal.z = mesh->mNormals[i].z;

				vertex.normal = normal;

				if (mesh->mTextureCoords[0]) {
					Vector2f uvCoord;
					uvCoord.x = mesh->mTextureCoords[0][i].x;
					uvCoord.y = mesh->mTextureCoords[0][i].y;

					vertex.uvCoord = uvCoord;
				} else
					vertex.uvCoord = Vector2f();

				vertices.push_back(&vertex);
			}

			for (int f = 0; f < mesh->mNumFaces; f++) {
				aiFace face = mesh->mFaces[f];
				for (int i = 0; i < face.mNumIndices; i++)
					indices.push_back(face.mIndices[i]);

				for (GLuint i = 0; i < mesh->mNumFaces; i++)
				{
					aiFace face = mesh->mFaces[i];
					for (GLuint j = 0; j < face.mNumIndices; j++)
						indices.push_back(face.mIndices[j]);
				}
			}

			if (mesh->mMaterialIndex >= 0) {
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

				vector<Texture> diffuseMaps = this->loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				vector<Texture> specularMaps = this->loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			}

			return Mesh(vertices, indices, textures);
		}

		std::vector<Texture> Model::loadMaterialTexture(aiMaterial* material, aiTextureType type, std::string typeName) {
			using namespace std;
			vector<Texture> textures;

			for (GLuint i = 0; i < material->GetTextureCount(type); i++) {
				Texture texture;

				aiString str;
				material->GetTexture(type, i, &str);

				graphics::Texture* gTexture = new graphics::Texture(str.C_Str());

				texture.id = gTexture->getTextureID();
				texture.type = typeName;
				texture.path = str;
				textures.push_back(texture);
			}
			return textures;
		}
}}