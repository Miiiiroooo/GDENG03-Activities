#include "AGameObject.h"
#include "ARenderer.h"


#pragma region Constructor-Destructor
AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->parent = NULL; 

	transform = new Transform();
	AttachComponent(transform);
}

AGameObject::~AGameObject()
{
	for (size_t i = 0; i < this->childList.size(); i++)
	{
		delete this->childList[i];
	}

	for (size_t i = 0; i < this->componentList.size(); i++) 
	{
		delete this->componentList[i]; 
	}

	transform = nullptr;

	this->childList.clear();
	this->childList.shrink_to_fit(); 
	this->componentList.clear(); 
	this->componentList.shrink_to_fit(); 
	 
	if (this->parent != NULL) 
	{
		this->parent = NULL; 
	}
}
#pragma endregion


#pragma region Game-related methods
//void AGameObject::ProcessInputs(sf::Event event)
//{
//	if (this->enabled)
//	{
//		std::vector<AComponent*> componentList = this->GetComponentsOfType(EComponentTypes::Input);
//
//		for (size_t i = 0; i < componentList.size(); i++)
//		{
//			GenericInputController* inputController = (GenericInputController*)componentList[i];
//			inputController->AssignEvent(event); 
//			inputController->Perform(); 
//		}
//
//		for (size_t i = 0; i < this->childList.size(); i++)
//		{
//			this->childList[i]->ProcessInputs(event); 
//		}
//	}
//}

void AGameObject::Update(float dt) 
{
	if (this->enabled)
	{
		std::vector<AComponent*> componentList = this->GetComponentsOfType(EComponentTypes::Script); 

		for (size_t i = 0; i < componentList.size(); i++)
		{
			componentList[i]->SetDeltaTime(dt);  
			componentList[i]->Perform(); 
		}


		for (size_t i = 0; i < childList.size(); i++)
		{
			childList[i]->Update(dt);  
		}
	}
}

void AGameObject::Draw()
{
	if (this->enabled) 
	{
		std::vector<AComponent*> rendererList = this->GetComponentsOfType(EComponentTypes::Renderer); 

		for (size_t i = 0; i < rendererList.size(); i++) 
		{
			ARenderer* renderer = (ARenderer*)rendererList[i];
			renderer->Perform();
		}

		for (size_t i = 0; i < childList.size(); i++) 
		{
			this->childList[i]->Draw(); 
		}
	}
}

std::string AGameObject::GetName()
{
	return this->name;
}

bool AGameObject::IsEnabled()
{
	return enabled;
}

void AGameObject::SetEnabled(bool flag)
{
	enabled = flag;
}
#pragma endregion


#pragma region Inheritance-related methods
void AGameObject::AttachChild(AGameObject* child)
{
	if (child == this)
	{
		return;
	}

	this->childList.push_back(child); 
	child->SetParent(this);
	child->Initialize(); 
}

void AGameObject::DetachChild(AGameObject* child)
{
	int index = -1;

	for (size_t i = 0; i < this->childList.size(); i++)
	{
		if (this->childList[i] == child) 
		{
			index = (int)i; 
		}
	}

	if (index != -1)
	{
		this->childList.erase(this->childList.begin() + index); 
	}

	child->SetParent(NULL); 

	//this->childList.erase(std::remove(this->childList.begin(), this->childList.end(), child), this->childList.end());
}

AGameObject* AGameObject::GetParent()
{
	return this->parent;
}

void AGameObject::SetParent(AGameObject* parent) 
{
	this->parent = parent; 
}
#pragma endregion


#pragma region Component-related methods
Transform* AGameObject::GetTransform()
{
	return transform;
}

void AGameObject::AttachComponent(AComponent* component)
{
	this->componentList.push_back(component);  
	component->AttachOwner(this);  
}

void AGameObject::DetachComponent(AComponent* component)
{
	int index = -1; 

	for (size_t i = 0; i < this->componentList.size(); i++) 
	{
		if (this->componentList[i] == component) 
		{
			index = (int)i; 
			this->componentList[i]->DetachOwner(); 
			break;
		}
	}

	if (index != -1) 
	{
		this->componentList.erase(this->componentList.begin() + index); 
	}
}

AComponent* AGameObject::FindComponentByName(std::string name)
{
	for (size_t i = 0; i < componentList.size(); i++) 
	{
		if (this->componentList[i]->GetName() == name) 
		{
			return this->componentList[i]; 
		}
	}

	return NULL;
}

AComponent* AGameObject::FindComponentByType(EComponentTypes type, std::string name)
{
	for (size_t i = 0; i < componentList.size(); i++)
	{
		if (this->componentList[i]->GetType() == type && this->componentList[i]->GetName() == name) 
		{
			return this->componentList[i]; 
		}
	}

	return NULL; 
}

std::vector<AComponent*> AGameObject::GetComponentsOfType(EComponentTypes type)
{
	if (type == EComponentTypes::Transform)
	{
		return { transform };
	}

	std::vector<AComponent*> foundList; 

	for (size_t i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->GetType() == type)
		{
			foundList.push_back(this->componentList[i]); 
		}
	}

	return foundList; 
}

std::vector<AComponent*> AGameObject::GetComponentsInChildrenOfType(EComponentTypes type)
{
	std::vector<AComponent*> foundList;

	for (int i = 0; i < childList.size(); i++)
	{
		std::vector<AComponent*> foundListInChild = childList[i]->GetComponentsOfType(type); ;
		
		/*std::vector<AComponent*> foundListInChild = (childList[i]->childList.size() > 0) ? 
			childList[i]->GetComponentsInChildrenOfType(type) :
			childList[i]->GetComponentsOfType(type);*/
		
		foundList.insert(foundList.end(), foundListInChild.begin(), foundListInChild.end());
	}

	return foundList;
}

////recursive implementation; also searches through its children
//std::vector<AComponent*> AGameObject::GetComponentsOfTypeRecursive(AComponent::ComponentType type)
//{
//	std::vector<AComponent*> foundList; 
//
//	for (size_t i = 0; i < this->componentList.size(); i++)
//	{
//		if (this->componentList[i]->getType() == type)
//		{
//			foundList.push_back(this->componentList[i]);
//		}
//	}
//
//	for (size_t i = 0; i < childList.size(); i++)
//	{
//		foundList = this->GetComponentRecursiveProper(this->childList[i], type, foundList); 
//	}
//
//	return foundList;
//}
//
//std::vector<AComponent*> AGameObject::GetComponentRecursiveProper(AGameObject* object, AComponent::ComponentType type, std::vector<AComponent*> foundList)
//{
//	return foundList; 
//}
#pragma endregion