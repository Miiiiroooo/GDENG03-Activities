#pragma once
#include "../AComponent.h"

class RotateScript : public AComponent
{
public:
	RotateScript();
	~RotateScript();

	void Clone(AComponent* copy) override;
	void Perform() override;


private:
	float xAngleSpeed;
	float yAngleSpeed;
	float zAngleSpeed;
};