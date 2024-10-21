#pragma once
#include "../AGameObject.h"
#include "../../Components/Renderer/MeshRenderer.h"

class CubeObject : public AGameObject
{
public:
	CubeObject(bool withColors);
	CubeObject(std::string name, bool withColors);
	~CubeObject();
	void Initialize() override;


private:
	MeshRenderer* renderer;
	bool withColors;
};