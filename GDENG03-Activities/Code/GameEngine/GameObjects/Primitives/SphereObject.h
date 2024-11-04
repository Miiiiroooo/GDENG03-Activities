#pragma once
#include "../AGameObject.h"
#include "GameEngine/Components/Renderer/MeshRenderer.h"

class SphereObject : public AGameObject 
{
public:
	SphereObject();
	SphereObject(std::string name);
	~SphereObject();
	void Initialize() override;


private:
	MeshRenderer* renderer;
};