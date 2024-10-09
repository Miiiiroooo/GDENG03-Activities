#include "CubeObject.h"
#include "../../Components/Renderer/MeshRenderer.h"
#include "../../Managers/GameObjectManager.h"

CubeObject::CubeObject() : AGameObject("CubeObj")
{

}

CubeObject::~CubeObject()
{

}

void CubeObject::Initialize()
{
	MeshRenderer* renderer1 = new MeshRenderer(L"DefaultShader");
	renderer1->LoadPrimitive(EPrimitiveMeshTypes::Cube);
	AttachComponent(renderer1);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer1);
}