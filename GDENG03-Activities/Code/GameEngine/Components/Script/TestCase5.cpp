#include "TestCase5.h"
#include "../Transform.h"
#include <cmath>

TestCase5::TestCase5() : AComponent("TestCase5", EComponentTypes::Script)
{
	currAngle = 90.f;
	angleSpeed = (float)rand() / (float)RAND_MAX * (60.f - 15.f) + 15.f;
}

TestCase5::~TestCase5()
{

}

void TestCase5::Clone(AComponent* copy)
{

}

void TestCase5::Perform()
{
	currAngle += angleSpeed * dt;

	float scaleX = Interpolate(1.0f, MAX_PLANE_SCALE, GetInterpolatedValue(currAngle));
	float scaleY = Interpolate(1.0f, MIN_PLANE_HEIGHT, GetInterpolatedValue(currAngle));
	float scaleZ = Interpolate(1.0f, MAX_PLANE_SCALE, GetInterpolatedValue(currAngle));

	transform->LocalScale = { scaleX, scaleY, scaleZ };
}

float TestCase5::GetInterpolatedValue(float angleInRad)
{
	return (std::cos(angleInRad * M_PI / 180.f) + 1) / 2.0f;
}

float TestCase5::Interpolate(float min, float max, float interpolation)
{
	return min + interpolation * (max - min);
}
