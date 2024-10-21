#pragma once
#include "../AComponent.h"

class TestCase5 : public AComponent
{
public:
	TestCase5();
	~TestCase5();

	void Clone(AComponent* copy) override;
	void Perform() override;

private:
	float GetInterpolatedValue(float angleInRad);
	float Interpolate(float min, float max, float interpolation);


private:
	const float MAX_PLANE_SCALE = 6.f;
	const float MIN_PLANE_HEIGHT = 0.0001f;
	float currAngle;
	float angleSpeed;
};