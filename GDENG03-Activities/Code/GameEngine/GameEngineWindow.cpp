#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"

#include "GameObjects/Primitives/CubeObject.h"
#include "GameObjects/Primitives/ConeObject.h"
#include "GameObjects/Primitives/CylinderObject.h"
#include "GameObjects/Primitives/SphereObject.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/FreeCameraObject.h"
#include "GameObjects/EmptyGameObject.h"
#include "Components/Scripts/CameraController.h"



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
	t1 = cube2->GetTransform();
	t1->Position = { 0, 0, 5 };
	t1->Rotate(45.0f, 0.0f, 45.0f);

	CylinderObject* cylinder2 = new CylinderObject();
	GameObjectManager::GetInstance()->AddObject(cylinder2);
	t2 = cylinder2->GetTransform(); 
	t2->Position = { 0, 0, -5 }; 
	t2->Rotate(30.0f, 0.0f, -45.0f);


	SphereObject* pawn = new SphereObject();
	GameObjectManager::GetInstance()->AddObject(pawn);
	pawn->GetTransform()->ScaleUniformly(2.f);

	ConeObject* shutter = new ConeObject();
	pawn->AttachChild(shutter);
	shutter->GetTransform()->Rotate(-90.0f, 0.0f, 0.0f);
	shutter->GetTransform()->LocalPosition = { 0.0f, 0.0f, 1.0f};
	shutter->GetTransform()->LocalScale = { 0.6f, 0.5f, 0.6f };

	FreeCameraObject* freeCam = new FreeCameraObject(width, height); 
	freeCam->GetTransform()->Position = { 0.0f, 0.0f, 0.0f }; 
	GameObjectManager::GetInstance()->AddObject(freeCam); 

	EmptyGameObject* e = new EmptyGameObject("CamController");  
	GameObjectManager::GetInstance()->AddObject(e);    

	CameraController* controller = new CameraController(freeCam, pawn);  
	e->AttachComponent(controller);  
	 

	Vector2 dir = Vector2::UnitY; 
	float currAngle = 0; 
	for (int i = 0; i < 4; i++)
	{
		dir.x = -sin(currAngle * M_PI / 180.f) * 15.f; 
		dir.y = -cos(currAngle * M_PI / 180.f) * 15.f;

		CameraObject* cam = new CameraObject(width, height);
		cam->GetTransform()->Position = { dir.x, 5.0f, dir.y };
		cam->GetTransform()->Rotate(10, currAngle, 0);
		GameObjectManager::GetInstance()->AddObject(cam);

		controller->AddCamera(cam->cameraComponent); 

		currAngle += 90;
	}

	CameraObject* cam5 = new CameraObject(width, height);   
	cam5->GetTransform()->Position = { 0.0f, 15.0f, -10.0f };  
	cam5->GetTransform()->Rotate(60, 0, 0);  
	GameObjectManager::GetInstance()->AddObject(cam5);  
	controller->AddCamera(cam5->cameraComponent);  
}

void GameEngineWindow::OnUpdate()
{
	swapChain->ClearBuffer(0.4f, 0.4f, 0.6f);

	currDelta += (float)EngineTime::GetDeltaTime();
	float secsPerFrame = 1.f / (float)fps;
	if (currDelta >= secsPerFrame) 
	{
		currDelta -= secsPerFrame; 
		GameObjectManager::GetInstance()->Update(secsPerFrame); 

		t1->Rotate(35 * secsPerFrame, -55 * secsPerFrame, 45 * secsPerFrame);
		t2->Rotate(-65 * secsPerFrame, 25 * secsPerFrame, -55 * secsPerFrame);

		Keyboard::FlushEventsBuffer();  
		Keyboard::FlushCharBuffer(); 
		Mouse::FlushEventsBuffer(); 
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