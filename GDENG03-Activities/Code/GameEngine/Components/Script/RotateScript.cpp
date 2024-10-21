#include "RotateScript.h"
#include "../Transform.h"

RotateScript::RotateScript() : AComponent("Spinner", EComponentTypes::Script)
{
	xAngleSpeed = (float)rand() / (float)RAND_MAX * 180 - 90;
	if (xAngleSpeed >= 0.f && xAngleSpeed < 5.0f) xAngleSpeed += 5.0f;
	else if (xAngleSpeed <= 0.f && xAngleSpeed > -5.0f) xAngleSpeed -= 5.0f;

	yAngleSpeed = (float)rand() / (float)RAND_MAX * 180 - 90;
	if (yAngleSpeed >= 0.f && yAngleSpeed < 5.0f) yAngleSpeed += 5.0f;
	else if (yAngleSpeed <= 0.f && yAngleSpeed > -5.0f) yAngleSpeed -= 5.0f;

	zAngleSpeed = (float)rand() / (float)RAND_MAX * 180 - 90;
	if (zAngleSpeed >= 0.f && zAngleSpeed < 5.0f) zAngleSpeed += 5.0f;
	else if (zAngleSpeed <= 0.f && zAngleSpeed > -5.0f) zAngleSpeed -= 5.0f;
}

RotateScript::~RotateScript()
{

}

void RotateScript::Clone(AComponent* copy)
{

}

void RotateScript::Perform()
{
	transform->Rotate(xAngleSpeed * dt, yAngleSpeed * dt, zAngleSpeed * dt);
}