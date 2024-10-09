#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"


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
	CubeObject* cube1 = new CubeObject();
	t1 = cube1->GetTransform(); 
	t1->Position = { 0.0f,  0.0f,  5.0f };
	GameObjectManager::GetInstance()->AddObject(cube1);

	CubeObject* cube2 = new CubeObject();
	cube1->AttachChild(cube2); 
	t2 = cube2->GetTransform(); 
	t2->Position = { 2.0f,  0.0f,  5.0f }; 

	CubeObject* cube3 = new CubeObject();
	cube2->AttachChild(cube3);
	t3 = cube3->GetTransform(); 
	t3->Position = { -2.0f,  0.0f,  5.0f }; 

	t2->Rotate(0, 0, 30);
	t2->Rotate(30, 0, 0);
	//t2->Rotate(t2->GetLocalRight(), 30);
}

void GameEngineWindow::OnUpdate()
{
	t1->Rotate(0, rSpeed * EngineTime::GetDeltaTime(), 0); 
	t2->Rotate(rSpeed * EngineTime::GetDeltaTime(), 0, 0); 
	t3->Rotate(0, rSpeed * EngineTime::GetDeltaTime(), 0); 

	/*t1->Rotate(Vector3::Up, rSpeed * EngineTime::GetDeltaTime());
	t2->Rotate(t2->GetLocalRight(), rSpeed * EngineTime::GetDeltaTime());
	t3->Rotate(t3->GetLocalUp(), rSpeed * EngineTime::GetDeltaTime());*/


	swapChain->ClearBuffer(0.4f, 0.4f, 0.6f);
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
