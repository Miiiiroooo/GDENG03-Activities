#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
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
	EmptyGameObject* empty1 = new EmptyGameObject("temp1");
	Transform* transform1 = empty1->GetTransform(); 
	transform1->Position = { 0.0f,  0.0f,  2.0f }; 
	//transform1->LocalScale = { 1.0f,  1.0f,  1.0f };
	GameObjectManager::GetInstance()->AddObject(empty1);

	MeshRenderer* renderer1 = new MeshRenderer(L"DefaultShader");
	renderer1->LoadPrimitive(EPrimitiveMeshTypes::Cube);
	empty1->AttachComponent(renderer1);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer1);
}

void GameEngineWindow::OnUpdate()
{
	swapChain->ClearBuffer(0.0f, 0.4f, 0.6f);
	//GameObjectManager::GetInstance()->ProcessInputs();
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
