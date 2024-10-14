#pragma once
#include <string>
#include "EComponentTypes.h"


class AGameObject;
class Transform;

class AComponent
{
public:
	AComponent(std::string name, EComponentTypes type);
	virtual ~AComponent();

	virtual void Clone(AComponent* copy) = 0;
	void AttachOwner(AGameObject* owner);
	void DetachOwner();
	AGameObject* GetOwner();
	EComponentTypes GetType();
	std::string GetName();

	void SetDeltaTime(float deltaTime);
	virtual void Perform() = 0;


protected:
	AGameObject* owner;
	Transform* transform;

	EComponentTypes type;
	std::string name;
	float dt;
};

