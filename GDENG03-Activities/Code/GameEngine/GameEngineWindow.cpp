#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"
#include "GameObjects/Primitives/PlaneObject.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/FreeCameraObject.h"


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
	/*CameraObject* cam = new CameraObject(width, height); 
	cam->GetTransform()->Position = { 0.0f, 0.0f, -15.0f }; 
	cam->GetTransform()->Rotate(10,0,0); 
	GameObjectManager::GetInstance()->AddObject(cam); */

	FreeCameraObject* cam = new FreeCameraObject(width, height); 
	cam->GetTransform()->Position = { 0.0f, 0.0f, -5.0f };
	//cam->GetTransform()->Rotate(10, 0, 0);
	GameObjectManager::GetInstance()->AddObject(cam);


	CubeObject* cube = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube);
	cube->GetTransform()->Position = { 0, 0, 0 };

	PlaneObject* plane = new PlaneObject();
	GameObjectManager::GetInstance()->AddObject(plane);
	plane->GetTransform()->Position = { 0, 0, 0 };


	/*CubeObject* cube1 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube1);
	t1 = cube1->GetTransform();
	t1->Position = { -10, 0, 0 };

	CubeObject* cube2 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube2);
	t2 = cube2->GetTransform();
	t2->Position = { 0, 0, 0 };

	CubeObject* cube3 = new CubeObject();
	cube2->AttachChild(cube3);
	t3 = cube3->GetTransform();
	t3->Position = { 10, 0, 0 };

	CubeObject* cube4 = new CubeObject();
	cube3->AttachChild(cube4);
	t4 = cube4->GetTransform();
	t4->Position = { 0, 0, 10 };

	CubeObject* cube5 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube5);
	cube5->GetTransform()->Position = { 0, 10, 0 };

	CubeObject* cube6 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube6);
	cube6->GetTransform()->Position = { 0, -10, 0 };

	CubeObject* cube7 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube7);
	cube7->GetTransform()->Position = { 0, 0, -10 };*/
}

void GameEngineWindow::OnUpdate()
{
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
