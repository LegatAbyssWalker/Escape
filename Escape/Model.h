#pragma once

#include "SFML/Graphics.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.h"
#include "Program.h"
#include "Variables.h"
#include "State.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

class Model {
	public:
		std::vector<Texture> textures_loaded;
		std::vector<Mesh> meshes;

		std::string directory;
		bool gamaCorrection;


	public:
		Model() = default;
		Model(std::string const& modelPath, GLWindow& window, bool gamma = false);

		void renderModel(std::unique_ptr<Program>& program);

	private:
		void loadModel(std::string const& path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);

		std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
		unsigned int textureFromFile(const char* path, const std::string &directory, bool gamma = false);
};

