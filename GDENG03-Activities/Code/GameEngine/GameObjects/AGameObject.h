#pragma once
#include <string>
#include <vector>
#include "../Components/AComponent.h"
#include "../Components/Transform.h"


class AGameObject
{
public:
	// Constructor-Destructor
	AGameObject(std::string name);
	~AGameObject();

	// Game-related methods
	virtual void Initialize() = 0;
	virtual void ProcessInputs(UINT msg);
	virtual void Update(float dt);
	virtual void Draw(); 

	std::string GetName();
	void SetName(std::string newName);
	__declspec(property(get = GetName, put = SetName)) std::string Name;
	bool IsEnabled();
	void SetEnabled(bool flag);
	__declspec(property(get = IsEnabled, put = SetEnabled)) bool Enabled;

	// Inheritance-related methods
	void AttachChild(AGameObject* child);
	void DetachChild(AGameObject* child);
	AGameObject* GetParent();

	// Component-related methods
	Transform* GetTransform();
	void AttachComponent(AComponent* component);
	void DetachComponent(AComponent* component);
	AComponent* FindComponentByName(std::string name);
	AComponent* FindComponentByType(EComponentTypes type, std::string name);
	std::vector<AComponent*> GetComponentsOfType(EComponentTypes type);
	std::vector<AComponent*> GetComponentsInChildrenOfType(EComponentTypes type);
	//std::vector<AComponent*> GetComponentsOfTypeRecursive(AComponent::ComponentType type);

private:
	void SetParent(AGameObject* parent);
	//std::vector<AComponent*> GetComponentRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList);


protected:
	std::string name;
	bool enabled = true;
	Transform* transform;

	AGameObject* parent;
	std::vector<AGameObject*> childList;
	std::vector<AComponent*> componentList; 
};

