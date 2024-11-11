#pragma once
#include "ARenderer.h"
#include "GameEngine/Meshes/EPrimitiveMeshTypes.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

class MeshRenderer : public ARenderer
{
public:
	MeshRenderer();
	MeshRenderer(AMaterial* material);
	~MeshRenderer();

	void LoadPrimitive(EPrimitiveMeshTypes type, bool isRainbowed = false);
	void LoadNonPrimitive(std::string modelName, bool isRainbowed = false);

private:
	void CreateNonPrimitiveColored(tinyobj::attrib_t& attributes, std::vector<tinyobj::shape_t>& shapes);
	void CreateNonPrimitiveTextured(tinyobj::attrib_t& attributes, std::vector<tinyobj::shape_t>& shapes);


private:
	const std::string STANDARD_MODEL_PATH = "Assets/Models/";
};