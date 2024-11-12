#pragma once
#include "ARenderer.h"
#include "GameEngine/Meshes/EPrimitiveMeshTypes.h"
#include <assimp/scene.h>

class MeshRenderer : public ARenderer
{
public:
	MeshRenderer();
	MeshRenderer(AMaterial* material);
	~MeshRenderer();

	void LoadPrimitive(EPrimitiveMeshTypes type, bool isRainbowed = false);
	void LoadNonPrimitive(std::string modelName, bool isRainbowed = false);

private:
	void CreateNonPrimitiveColored(const aiScene* model);
	void CreateNonPrimitiveTextured(const aiScene* model);


private:
	const std::string STANDARD_MODEL_PATH = "Assets/Models/";
};