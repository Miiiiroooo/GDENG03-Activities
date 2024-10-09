#pragma once
#include "../AGameObject.h"

class CubeObject : public AGameObject
{
public:
	CubeObject();
	~CubeObject();
	void Initialize() override;
};