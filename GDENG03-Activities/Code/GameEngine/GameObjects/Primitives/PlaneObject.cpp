#include "PlaneObject.h"
#include "../../Managers/GameObjectManager.h"

PlaneObject::PlaneObject() : AGameObject("PlaneObject")
{

}

PlaneObject::PlaneObject(std::string name) : AGameObject(name)
{

}

PlaneObject::~PlaneObject()
{
	if (renderer) renderer->Release();
}

void PlaneObject::Initialize()
{
	renderer = new MeshRenderer(L"DefaultShader");
	renderer->LoadPrimitive(EPrimitiveMeshTypes::Plane);
	AttachComponent(renderer);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer);

	isInitialized = true;
}