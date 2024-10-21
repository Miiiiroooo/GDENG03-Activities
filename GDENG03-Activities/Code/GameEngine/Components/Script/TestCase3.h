#pragma once
#include "../AComponent.h"

class TestCase3 : public AComponent
{
public:
	TestCase3();
	~TestCase3();

	void Clone(AComponent* copy) override;
	void Perform() override;

private:
	float GetInterpolatedValue(float angleInRad);
	float Interpolate(float min, float max, float interpolation);


private:
	const float MAX_SCALE = 1.0f;
	const float MIN_SCALE = 0.25f;
	float max_X;
	float min_X;
	float max_Y;
	float min_Y;

	float currAngle[3];
	float angleSpeed[3];
};