#pragma once
#include <vector>
#include "../AComponent.h"
#include "../../GameObjects/Primitives/CircleObject.h"


class CircleSpawner : public AComponent
{
public:
	CircleSpawner(float aspectRatio);
	~CircleSpawner();

	void Perform() override;
	void CreateCircle();
	void DeleteRecentCircle();
	void DeleteAllCircles();


private:
	float aspectRatio;
	std::vector<CircleObject*> circlesList;
};