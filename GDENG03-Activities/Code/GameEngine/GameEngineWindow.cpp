#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"

#include "GameObjects/EmptyGameObject.h"
#include "Components/Scripts/CircleSpawner.h"
#include "Components/Inputs/CircleSpawnerInputListener.h"


GameEngineWindow::GameEngineWindow(int fps) : fps(fps), currDelta(0.f)
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
	CircleSpawner* spawner = new CircleSpawner((float)width / (float)height);
	e1->AttachComponent(spawner);
	CircleSpawnerInputListener* input = new CircleSpawnerInputListener(spawner);
	e1->AttachComponent(input);
	GameObjectManager::GetInstance()->AddObject(e1);

}

void GameEngineWindow::OnUpdate()
{
	swapChain->ClearBuffer(0.f, 0.f, 0.f); 

	currDelta += EngineTime::GetDeltaTime(); 

	if (currDelta >= 1.f / (float)fps) 
	{
		currDelta -= 1.f / (float)fps;
		GameObjectManager::GetInstance()->Update(1.f / (float)fps);
	}

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
	switch (msg)
	{
		case WM_SYSKEYDOWN: 
			if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000) 
			{
				
			}
			GameObjectManager::GetInstance()->ProcessInputs(wParam, lParam);
			break;

		case WM_KEYDOWN: 
		case WM_KEYUP: 
		case WM_SYSKEYUP:
		{
			if (wParam == VK_ESCAPE)
			{
				OnDestroy(); 
				PostQuitMessage(0);  
			}

			GameObjectManager::GetInstance()->ProcessInputs(wParam, lParam);
			break;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
