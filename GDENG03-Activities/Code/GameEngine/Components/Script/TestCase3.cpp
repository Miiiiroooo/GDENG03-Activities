#include "TestCase3.h"
#include "../Transform.h"
#include <cmath>

TestCase3::TestCase3() : AComponent("TestCase3", EComponentTypes::Script)
{
	max_X = (float)rand() / (float)RAND_MAX * 3;
	min_X = (float)rand() / (float)RAND_MAX * 3 - 3;
	max_Y = (float)rand() / (float)RAND_MAX * 3;
	min_Y = (float)rand() / (float)RAND_MAX * 3 - 3;

	for (int i = 0; i < 3; i++)
	{
		currAngle[i] = 90.f;
		angleSpeed[i] = (float)rand() / (float)RAND_MAX * (60.f - 15.f) + 15.f;
	}
}

TestCase3::~TestCase3()
{

}

void TestCase3::Clone(AComponent* copy)
{

}

void TestCase3::Perform()
{
	for (int i = 0; i < 3; i++)
	{
		currAngle[i] += angleSpeed[i] * dt;
	}

	float newX = Interpolate(min_X, max_X, GetInterpolatedValue(currAngle[0]));
	float newY = Interpolate(min_Y, max_Y, GetInterpolatedValue(currAngle[1]));
	transform->Position = { newX, newY, transform->Position.z };

	float scale = Interpolate(MIN_SCALE, MAX_SCALE, GetInterpolatedValue(currAngle[2]));
	transform->LocalScale = { scale, scale, scale };
}

float TestCase3::GetInterpolatedValue(float angleInRad)
{
	return (std::cos(angleInRad * M_PI / 180.f) + 1) / 2.0f;
}

float TestCase3::Interpolate(float min, float max, float interpolation)
{
	return min + interpolation * (max - min);
}
