#pragma once
#include "ARenderer.h"
#include "../../Meshes/EPrimitiveMeshTypes.h"

class MeshRenderer : public ARenderer
{
public:
	MeshRenderer();
	MeshRenderer(LPCWSTR shaderType);
	~MeshRenderer();

	void LoadPrimitive(EPrimitiveMeshTypes type);
	void LoadNonPrimitive(std::string fileName);


	void Temp(const std::vector<DirectX::XMFLOAT3>& colorList);
	void CreateCircle(Vector3 color);
};