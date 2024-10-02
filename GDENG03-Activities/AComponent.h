#pragma once
#include <string>
#include "EComponentTypes.h"

class AGameObject;

class AComponent
{
public:
	AComponent(std::string name, EComponentTypes type);
	virtual ~AComponent();

	void AttachOwner(AGameObject* owner);
	void DetachOwner();
	AGameObject* GetOwner();
	EComponentTypes GetType();
	std::string GetName();

	void SetDeltaTime(float deltaTime);
	virtual void Perform() = 0;


protected:
	AGameObject* owner;
	EComponentTypes type;
	std::string name;
	float deltaTimeInSeconds;
};

