#pragma once
#include <SimpleMath.h>
#include "../AComponent.h"


using namespace DirectX::SimpleMath;

class CircleBehavior : public AComponent
{
public:
	CircleBehavior();
	~CircleBehavior();

	void Perform() override;


private:
	static float speed;
	Vector2 dir;
};