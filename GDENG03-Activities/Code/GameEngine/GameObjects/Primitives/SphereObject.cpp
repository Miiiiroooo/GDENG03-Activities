#include "SphereObject.h"
#include "GameEngine/Managers/GameObjectManager.h"

SphereObject::SphereObject() : AGameObject("SphereObject")
{

}

SphereObject::SphereObject(std::string name) : AGameObject(name)
{

}

SphereObject::~SphereObject()
{
	if (renderer) renderer->Release();
}

void SphereObject::Initialize()
{
	renderer = new MeshRenderer(L"DefaultShader");
	renderer->LoadPrimitive(EPrimitiveMeshTypes::Sphere);
	AttachComponent(renderer);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer);

	isInitialized = true;
}