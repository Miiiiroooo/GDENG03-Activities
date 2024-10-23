#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"


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
	cam->GetTransform()->Position = { 0.0f, 0.0f, -15.0f };
	cam->GetTransform()->Rotate(10,0,0);
	GameObjectManager::GetInstance()->AddObject(cam);


	CubeObject* cube1 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube1);
	t1 = cube1->GetTransform();
	t1->Position = { -4, 0, 0 };

	CubeObject* cube2 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube2);
	t2 = cube2->GetTransform();
	t2->Position = { 0, 0, 0 };

	CubeObject* cube3 = new CubeObject();
	cube2->AttachChild(cube3);
	//GameObjectManager::GetInstance()->AddObject(cube3);
	t3 = cube3->GetTransform();
	t3->Position = { 3, 0, 1 };
	//t3->Rotate(50, 0, 20);

	CubeObject* cube4 = new CubeObject();
	cube3->AttachChild(cube4);
	//GameObjectManager::GetInstance()->AddObject(cube4);
	t4 = cube4->GetTransform();
	t4->Position = { 6, 0, 0 };

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
	t1->Rotate(0, 20 * EngineTime::GetDeltaTime(), 0);
	t2->Rotate(20 * EngineTime::GetDeltaTime(), 0, 0);
	t3->Rotate(0, 0, 20 * EngineTime::GetDeltaTime());




	swapChain->ClearBuffer(0.4f, 0.4f, 0.6f);

	currDelta += EngineTime::GetDeltaTime();
	float secsPerFrame = 1.f / (float)fps;
	if (currDelta >= secsPerFrame) 
	{
		currDelta -= secsPerFrame; 
		GameObjectManager::GetInstance()->Update(secsPerFrame);

		Keyboard::GetInstance()->FlushEventsBuffer(); 
		Keyboard::GetInstance()->FlushCharBuffer();
		Mouse::GetInstance()->FlushEventsBuffer();
	}

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

	return Window::HandleWindowMessages(hWnd, msg, wParam, lParam);
}
