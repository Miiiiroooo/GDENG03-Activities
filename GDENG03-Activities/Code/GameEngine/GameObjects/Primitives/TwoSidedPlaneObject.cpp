#include "TwoSidedPlaneObject.h"
#include "../../Managers/GameObjectManager.h"

TwoSidedPlaneObject::TwoSidedPlaneObject() : AGameObject("PlaneObject")
{

}

TwoSidedPlaneObject::TwoSidedPlaneObject(std::string name) : AGameObject(name)
{

}

TwoSidedPlaneObject::~TwoSidedPlaneObject()
{
	if (renderer) renderer->Release();
}

void TwoSidedPlaneObject::Initialize()
{
	renderer = new MeshRenderer(L"DefaultShader");
	renderer->LoadPrimitive(EPrimitiveMeshTypes::TwoSidedPlane);
	AttachComponent(renderer); 
	GameObjectManager::GetInstance()->BindRendererToShader(renderer);

	isInitialized = true;
}