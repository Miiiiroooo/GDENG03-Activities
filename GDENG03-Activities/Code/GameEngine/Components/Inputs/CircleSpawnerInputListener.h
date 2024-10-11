#pragma once
#include "GenericInputController.h"
#include "../Scripts/CircleSpawner.h"


class CircleSpawnerInputListener : public GenericInputController
{
public:
	CircleSpawnerInputListener(CircleSpawner* spawner);
	~CircleSpawnerInputListener();

	void Perform() override;


private:
	CircleSpawner* spawner;
};