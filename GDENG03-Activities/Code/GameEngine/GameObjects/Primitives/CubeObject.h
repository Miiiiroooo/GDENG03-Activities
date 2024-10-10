#pragma once
#include "../AGameObject.h"

class CubeObject : public AGameObject
{
public:
	CubeObject();
	CubeObject(std::string name);
	~CubeObject();
	void Initialize() override;
};