#include "CircleSpawner.h"
#include "../../Managers/GameObjectManager.h"


CircleSpawner::CircleSpawner(float aspectRatio) : AComponent("CircleSpawner", EComponentTypes::Script), aspectRatio(aspectRatio)
{

}

CircleSpawner::~CircleSpawner()
{

}

void CircleSpawner::Perform()
{

}

void CircleSpawner::CreateCircle()
{
	CircleObject* newCircle = new CircleObject(aspectRatio);
	owner->AttachChild(newCircle);
	circlesList.push_back(newCircle);
}

void CircleSpawner::DeleteRecentCircle()
{
	if (circlesList.size() == 0) return;

	CircleObject* circle = circlesList.back(); 
	circlesList.erase(circlesList.begin() + circlesList.size() - 1);
	circlesList.shrink_to_fit();
	GameObjectManager::GetInstance()->DeleteObject(circle);
}

void CircleSpawner::DeleteAllCircles()
{
	for (int i = circlesList.size() - 1; i >= 0; i--)
	{
		DeleteRecentCircle();
	}
}