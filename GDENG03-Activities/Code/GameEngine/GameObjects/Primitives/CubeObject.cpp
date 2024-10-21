#include "CubeObject.h"
#include "../../Managers/GameObjectManager.h"

CubeObject::CubeObject(bool withColors) : AGameObject("CubeObj"), withColors(withColors)
{

}

CubeObject::CubeObject(std::string name, bool withColors) : AGameObject(name), withColors(withColors)
{

}

CubeObject::~CubeObject()
{
	if (renderer) renderer->Release();
}

void CubeObject::Initialize()
{
	renderer = new MeshRenderer(L"DefaultShader");
	if (withColors) renderer->LoadCubeWithColors();
	else renderer->LoadPrimitive(EPrimitiveMeshTypes::Cube); 
	AttachComponent(renderer);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer);

	isInitialized = true;
}