#pragma once

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(std::string const &path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
	std::vector<Mesh>meshes;
	std::string directory;
	std::vector<SimpleTextureStruct>textures_loaded;
	bool gammaCorrection;

private:
	void loadModel(const std::string &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<SimpleTextureStruct> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);



};