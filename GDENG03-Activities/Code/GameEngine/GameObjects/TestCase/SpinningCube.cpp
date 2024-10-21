#include "SpinningCube.h"
#include "../../Components/Renderer/MeshRenderer.h"
#include "../../Components/Script/RotateScript.h"
#include "../../Managers/GameObjectManager.h"

SpinningCube::SpinningCube() : AGameObject("SpinnyBoi")
{
	shaderType = L"";
}

SpinningCube::SpinningCube(LPCWSTR shaderType) : AGameObject("SpinnyBoi"), shaderType(shaderType)
{

}

SpinningCube::~SpinningCube()
{

}

void SpinningCube::Initialize()
{
	MeshRenderer* mr;
	if (shaderType != L"") mr = new MeshRenderer(shaderType);
	else mr = new MeshRenderer(L"DefaultShader");
	mr->LoadPrimitive(EPrimitiveMeshTypes::Cube);
	AttachComponent(mr);
	GameObjectManager::GetInstance()->BindRendererToShader(mr);

	RotateScript* rs = new RotateScript();
	AttachComponent(rs);

	isInitialized = true;
}