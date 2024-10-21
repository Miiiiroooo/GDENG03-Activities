#pragma once
#include "../AGameObject.h"
#include "../../Components/Renderer/MeshRenderer.h"

class TwoSidedPlaneObject : public AGameObject
{
public:
	TwoSidedPlaneObject();
	TwoSidedPlaneObject(std::string name);
	~TwoSidedPlaneObject();
	void Initialize() override;


private:
	MeshRenderer* renderer;
};