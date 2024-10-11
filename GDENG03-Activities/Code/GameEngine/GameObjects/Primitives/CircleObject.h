#pragma once
#include "../AGameObject.h"

class CircleObject : public AGameObject
{
public:
	CircleObject(float aspectRatio);
	~CircleObject();

	void Initialize() override;


private:
	float aspectRatio;
	float randScale;
};