#include "CubeObject.h"
#include "../../Managers/GameObjectManager.h"

CubeObject::CubeObject() : AGameObject("CubeObj")
{

}

CubeObject::CubeObject(std::string name) : AGameObject(name)
{

}

CubeObject::~CubeObject()
{
	if (renderer) renderer->Release();
}

void CubeObject::Initialize()
{
	renderer = new MeshRenderer(L"DefaultShader");
	renderer->LoadPrimitive(EPrimitiveMeshTypes::Cube);
	AttachComponent(renderer);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer);
}