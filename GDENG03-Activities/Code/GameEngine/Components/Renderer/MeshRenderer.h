#pragma once
#include "ARenderer.h"
#include "GameEngine/Meshes/EPrimitiveMeshTypes.h"

class MeshRenderer : public ARenderer
{
public:
	MeshRenderer();
	MeshRenderer(LPCWSTR shaderType);
	~MeshRenderer();

	void LoadPrimitive(EPrimitiveMeshTypes type);
	void LoadNonPrimitive(std::string fileName);
};