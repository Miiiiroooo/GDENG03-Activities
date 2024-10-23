#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"
#include "GameObjects/Primitives/ConeObject.h"
#include "GameObjects/Primitives/CylinderObject.h"
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
	GameObjectManager::GetInstance()->AddObject(cam);


	CubeObject* cube1 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube1);
	cube1->GetTransform()->Position = { 0, 0, 0 };

	ConeObject* cone = new ConeObject();
	GameObjectManager::GetInstance()->AddObject(cone);
	cone->GetTransform()->Position = { 5, 0, 0 };

	CylinderObject* cylinder1 = new CylinderObject();
	GameObjectManager::GetInstance()->AddObject(cylinder1);
	cylinder1->GetTransform()->Position = { -5, 0, 0 };

	CubeObject* cube2 = new CubeObject();
	GameObjectManager::GetInstance()->AddObject(cube2);
	cube2->GetTransform()->Position = { 0, 0, 5 };
	cube2->GetTransform()->Rotate(0.0f, 0.0f, 45.0f);

	CylinderObject* cylinder2 = new CylinderObject();
	GameObjectManager::GetInstance()->AddObject(cylinder2);
	t1 = cylinder2->GetTransform(); 
	t1->Position = { 0, 0, -5 }; 
	t1->Rotate(30.0f, 0.0f, -45.0f);
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

		t1->Rotate(35 * secsPerFrame, -55 * secsPerFrame, 45 * secsPerFrame);

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
