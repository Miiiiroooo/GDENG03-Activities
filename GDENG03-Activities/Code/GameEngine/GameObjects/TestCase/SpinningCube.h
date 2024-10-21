#pragma once
#include "../AGameObject.h"

class SpinningCube : public AGameObject
{
public:
	SpinningCube();
	SpinningCube(LPCWSTR shaderType);
	~SpinningCube();

	void Initialize() override;


private:
	LPCWSTR shaderType;
};