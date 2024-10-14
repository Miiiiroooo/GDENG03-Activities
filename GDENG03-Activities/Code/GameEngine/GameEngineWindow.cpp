#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"
#include "GameObjects/Primitives/PlaneObject.h"


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
	cam = new CameraObject(width, height);
	cam->GetTransform()->Position = { 0.0f, 1.0f, -10.0f };
	cam->GetTransform()->Rotate(10,0,0);
	GameObjectManager::GetInstance()->AddObject(cam);


	CubeObject* cube = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube);
	PlaneObject* plane = new PlaneObject();
	GameObjectManager::GetInstance()->AddObject(plane);


	/*CubeObject* c1 = new CubeObject("c1");
	c1->GetTransform()->Position = { 0.0f, 2.0f, 5.0f };
	GameObjectManager::GetInstance()->AddObject(c1);
	t1 = c1->GetTransform();  
	
	CubeObject* c2 = new CubeObject("c2");
	c2->GetTransform()->Position = { 2.0f, 0.0f, 5.0f };
	c1->AttachChild(c2);
	t2 = c2->GetTransform(); 

	CubeObject* c3 = new CubeObject("c3");
	c3->GetTransform()->Position = { -2.0f, 0.0f, 4.0f };
	c2->AttachChild(c3);
	t3 = c3->GetTransform(); */
}

void GameEngineWindow::OnUpdate()
{
	//t1->Rotate(0, 20 * EngineTime::GetDeltaTime(), 0);
	//t2->Rotate(20 * EngineTime::GetDeltaTime(), 0, 0);
	//t3->Rotate(0, 0, 20 * EngineTime::GetDeltaTime());


	swapChain->ClearBuffer(0.4f, 0.4f, 0.6f);

	currDelta += EngineTime::GetDeltaTime();

	if (currDelta >= 1.f / (float)fps)
	{
		currDelta -= 1.f / (float)fps;
		GameObjectManager::GetInstance()->Update(1.f / (float)fps);
	}

	cam->cameraComponent->BindVPMatrixToPipeline();

	GameObjectManager::GetInstance()->Draw();
	swapChain->Present(true);
}

void GameEngineWindow::OnDestroy()
{
	Window::OnDestroy();

	GraphicsEngine::GetInstance()->Release();
	// engine time???
	// other more managers???
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
