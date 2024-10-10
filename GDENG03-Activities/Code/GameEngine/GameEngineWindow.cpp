#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"

#include "GameObjects/EmptyGameObject.h"
#include "Components/Renderer/MeshRenderer.h"


GameEngineWindow::GameEngineWindow()
{
	windowClassName = "GameEngineClass";
}

GameEngineWindow::~GameEngineWindow()
{ 

}

void GameEngineWindow::OnCreate(HWND hWnd)
{
	// initialize game engine
	GraphicsEngine::GetInstance()->Init();
	GraphicsEngine::GetInstance()->SetViewport(windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);
	swapChain = GraphicsEngine::GetInstance()->CreateSwapChain(hWnd, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);
	EngineTime::Initialize();


	// setup the objects
	EmptyGameObject* e1 = new EmptyGameObject("e1");
	MeshRenderer* mr1 = new MeshRenderer(L"DefaultShader");
	mr1->LoadPrimitive(EPrimitiveMeshTypes::Circle);
	e1->AttachComponent(mr1);
	GameObjectManager::GetInstance()->BindRendererToShader(mr1);
	GameObjectManager::GetInstance()->AddObject(e1);
	e1->GetTransform()->LocalScale = Vector3(0.3f, (float)width / (float)height * 0.3f, 1);

}

void GameEngineWindow::OnUpdate(UINT msg)
{
	swapChain->ClearBuffer(0.f, 0.f, 0.f);
	GameObjectManager::GetInstance()->ProcessInputs(msg);
	GameObjectManager::GetInstance()->Update(EngineTime::GetDeltaTime());
	GameObjectManager::GetInstance()->Draw();
	swapChain->Present(true);
}

void GameEngineWindow::OnDestroy()
{
	Window::OnDestroy();

	GraphicsEngine::GetInstance()->Release();
}

LRESULT GameEngineWindow::HandleWindowMessages(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
