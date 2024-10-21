#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/Primitives/CubeObject.h"

#include "GameObjects/TestCase/SpinningCube.h"
#include "GameObjects/Primitives/PlaneObject.h"
#include "GameObjects/Primitives/TwoSidedPlaneObject.h"
#include "Components/Script/TestCase3.h"
#include "Components/Script/TestCase5.h"


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
	cam->GetTransform()->Position = { 0.0f, 0.0f, -10.0f };
	GameObjectManager::GetInstance()->AddObject(cam);


	// Test Case 1
	/*CubeObject* cube = new CubeObject(true);    
	GameObjectManager::GetInstance()->AddObject(cube);   
	cube->GetTransform()->Position = { 0, 0, 0 }; 
	cube->GetTransform()->Rotate(30, 30, 30); */

	// Test Case 2
	/*SpinningCube* cube = new SpinningCube(); 
	GameObjectManager::GetInstance()->AddObject(cube); 
	cube->GetTransform()->Position = { 0, 0, 2 }; */

	// Test Case 3
	/*CubeObject* cube = new CubeObject(true); 
	GameObjectManager::GetInstance()->AddObject(cube); 
	cube->GetTransform()->Position = { 0, 0, 2 }; 

	TestCase3* script = new TestCase3(); 
	cube->AttachComponent(script); */

	// Test Case 4
	/*for (int i = 0; i < 50; i++) 
	{
		float randX = (float)rand() / (float)RAND_MAX * 8 - 4; 
		float randY = (float)rand() / (float)RAND_MAX * 8 - 4; 
		float randZ = (float)rand() / (float)RAND_MAX * 8; 

		SpinningCube* cube = new SpinningCube();  
		GameObjectManager::GetInstance()->AddObject(cube);  
		cube->GetTransform()->Position = { randX, randY, randZ }; 
	}*/

	// Test Case 5
	/*cam->GetTransform()->Position = { 5.0f, 5.0f, -10.0f }; 
	cam->GetTransform()->Rotate(25, -30, 0);  

	CubeObject* cube = new CubeObject(true);  
	GameObjectManager::GetInstance()->AddObject(cube);  

	TestCase5* script = new TestCase5();  
	cube->AttachComponent(script);  */

	// Test Case 6
	/*cam->GetTransform()->Position = { 6.0f, 3.0f, -5.0f }; 
	cam->GetTransform()->Rotate(15, -50, 0); 

	CubeObject* cube1 = new CubeObject(true); 
	GameObjectManager::GetInstance()->AddObject(cube1); 
	cube1->GetTransform()->Position = { 0.0f, 0.9f, 0.0f }; 

	CubeObject* cube2 = new CubeObject(true);
	GameObjectManager::GetInstance()->AddObject(cube2);
	cube2->GetTransform()->Position = { -1.5f, 2.0f, 0.0f };

	CubeObject* cube3 = new CubeObject(true);
	GameObjectManager::GetInstance()->AddObject(cube3);
	cube3->GetTransform()->Position = { -1.5f, 3.0f, -2.0f };

	PlaneObject* plane = new PlaneObject();
	GameObjectManager::GetInstance()->AddObject(plane);
	plane->GetTransform()->LocalScale = { 2.0f, 2.0f, 2.0f };*/

	// Test Case 7
	cam->GetTransform()->Position = { 6.0f, 5.0f, -7.5f }; 
	cam->GetTransform()->Rotate(25, -35, 0); 

	for (int i = 0; i < 3; i++) 
	{
		int numCardsInRow = (i + 1) * 2;  
		for (int j = 0; j < numCardsInRow; j++)  
		{
			TwoSidedPlaneObject* newCard = new TwoSidedPlaneObject(); 
			GameObjectManager::GetInstance()->AddObject(newCard); 

			Transform* t = newCard->GetTransform(); 
			t->LocalScale = { 0.3f, 0.0f, 0.2f }; 
			t->Rotate(0.0f, 0.0f, (j % 2 == 0) ? 60 : -60); 

			float x = 0.4f * (j * 2  - (numCardsInRow - 1)); 
			float y = (2 - i) * 1.3f; 
			t->Position = { x, y, 0 }; 
		}
	}

	TwoSidedPlaneObject* flatCard1 = new TwoSidedPlaneObject(); 
	GameObjectManager::GetInstance()->AddObject(flatCard1); 
	flatCard1->GetTransform()->Position = { 0.0f, 1.95f, 0.0f }; 
	flatCard1->GetTransform()->LocalScale = { 0.3f, 0.0f, 0.2f }; 

	TwoSidedPlaneObject* flatCard2 = new TwoSidedPlaneObject(); 
	GameObjectManager::GetInstance()->AddObject(flatCard2); 
	flatCard2->GetTransform()->Position = { -0.8f, 0.65f, 0.0f }; 
	flatCard2->GetTransform()->LocalScale = { 0.3f, 0.0f, 0.2f }; 

	TwoSidedPlaneObject* flatCard3 = new TwoSidedPlaneObject(); 
	GameObjectManager::GetInstance()->AddObject(flatCard3); 
	flatCard3->GetTransform()->Position = { 0.8f, 0.65f, 0.0f }; 
	flatCard3->GetTransform()->LocalScale = { 0.3f, 0.0f, 0.2f };  
}

void GameEngineWindow::OnUpdate()
{
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
