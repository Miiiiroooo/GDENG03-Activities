#pragma once
#include "../AGameObject.h"
#include "GameEngine/Components/Renderer/MeshRenderer.h"

class QuadObject : public AGameObject
{
public:
	QuadObject();
	QuadObject(std::string name);
	~QuadObject();
	void Initialize() override;


private:
	MeshRenderer* renderer;
};