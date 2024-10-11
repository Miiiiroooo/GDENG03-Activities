#include "CircleBehavior.h"
#include "../Transform.h"


float CircleBehavior::speed = 0.5f;

CircleBehavior::CircleBehavior() : AComponent("CircleBehavior", EComponentTypes::Script)
{
	float randX = (float)rand() / (float)RAND_MAX * 2.f - 1.f;
	float randY = (float)rand() / (float)RAND_MAX * 2.f - 1.f;
	dir = Vector2(randX, randY);
	dir.Normalize();
}

CircleBehavior::~CircleBehavior()
{

}

void CircleBehavior::Perform()
{
	Vector2 newPos = transform->Position + dir * speed * deltaTimeInSeconds;

	dir.x *= ((newPos.x + transform->LocalScale.x / 2.f >= 1.f) || (newPos.x - transform->LocalScale.x / 2.f <= -1.f)) ? -1 : 1;
	dir.y *= ((newPos.y + transform->LocalScale.y / 2.f >= 1.f) || (newPos.y - transform->LocalScale.y / 2.f <= -1.f)) ? -1 : 1;

	transform->Position = Vector3(newPos.x, newPos.y, 1);
}