#include "GameObjectManager.h"
#include "ShaderManager.h"


GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::GetInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new GameObjectManager(); 
	}

	return sharedInstance; 
}


#pragma region Game-related methods
//void GameObjectManager::ProcessInput(sf::Event event)
//{
//	for (size_t i = 0; i < gameObjectList.size(); i++) 
//	{
//		gameObjectList[i]->ProcessInputs(event); 
//	}
//}

void GameObjectManager::Update(float deltaTime)
{
	for (size_t i = 0; i < gameObjectList.size(); i++)
	{
		gameObjectList[i]->Update(deltaTime);
	}
}

void GameObjectManager::Draw()
{
	auto shadersList = ShaderManager::GetInstance()->GetShaderProgramsList();

	for (size_t i = 0; i < shadersList.size(); i++)
	{
		shadersList[i].vShader->BindToPipeline();
		shadersList[i].pShader->BindToPipeline();

		LPCWSTR shaderType = shadersList[i].shaderType;
		auto objectsList = shaderToObjectsMap[shaderType];

		for (size_t j = 0; j < objectsList.size(); j++)
		{
			objectsList[j]->Draw();
		}
	}
}
#pragma endregion


#pragma region Object-related methods
void GameObjectManager::AddObject(AGameObject* gameObject)
{
	gameObjectMap[gameObject->GetName()] = gameObject; 
	gameObjectList.push_back(gameObject); 
	gameObject->Initialize(); 
}

void GameObjectManager::BindRendererToShader(ARenderer* rendererComponent)
{
	LPCWSTR shaderType = rendererComponent->GetShaderType();
	shaderToObjectsMap[shaderType].push_back(rendererComponent->GetOwner());
}

AGameObject* GameObjectManager::FindObjectByName(std::string name)
{
	if (gameObjectMap[name] != NULL)
	{
		return gameObjectMap[name];
	}
	else
	{
		//std::cout << "Object " << name << " not found!" << std::endl;
		return NULL;
	}
}

void GameObjectManager::DeleteObject(AGameObject* gameObject)
{
	std::string key = gameObject->GetName(); 
	delete gameObject; 

	gameObjectMap.erase(key); 
	gameObjectList.erase(std::remove(gameObjectList.begin(), gameObjectList.end(), gameObject)); 
	gameObjectList.shrink_to_fit(); 
}

void GameObjectManager::DeleteObjectByName(std::string name)
{
	AGameObject* object = FindObjectByName(name);

	if (object != NULL)
	{
		DeleteObject(object); 
	}
}

std::vector<AGameObject*> GameObjectManager::GetAllObjects()
{
	return gameObjectList;
}

int GameObjectManager::GetActiveObjectsCount()
{
	return (int)gameObjectList.size();
}
#pragma endregion