#include "GameEngineWindow.h"
#include "Debug.h"
#include "EngineTime.h"
#include "EditorGUI/EditorGUIManager.h"
#include "Managers/GameObjectManager.h"
#include "Managers/PhysicsEngine.h"
#include "WindowSystem/FileDialogs.h"
#include "GameObjects/FreeCameraObject.h"

#include "GameObjects/Primitives/CubeObject.h"
#include "GameObjects/Primitives/ConeObject.h"
#include "GameObjects/Primitives/CylinderObject.h"
#include "GameObjects/Primitives/SphereObject.h"
#include "GameObjects/Primitives/PlaneObject.h"
#include "GameObjects/Primitives/CapsuleObject.h"
#include "GameObjects/ModelObject.h"
#include "GameObjects/PhysicsObject.h"
#include "Managers/PhysicsEngine.h"
#include "MathUtils.h"

#include "EditorStates/EditorBackend.h"
#include <EditorStates/EditorActions/EditorActionHistory.h>

GameEngineWindow::GameEngineWindow(int fps) : fps(fps), accumulator(0.f)
{
	windowClassName = "GameEngineClass";
}

GameEngineWindow::~GameEngineWindow()
{ 

}

void GameEngineWindow::OnCreate(HWND hWnd)
{
	// initialize game engine
	EditorActionHistory::initialize();
	EditorBackend::initialize();
	Debug::initialize();

	GraphicsEngine::GetInstance()->Init();
	GraphicsEngine::GetInstance()->SetViewport(width, height); 
	swapChain = GraphicsEngine::GetInstance()->CreateSwapChain(hWnd, width, height); 

	EngineTime::Initialize();
	EditorGUIManager::GetInstance()->Initialize(hWnd); 
	PhysicsEngine::GetInstance()->Init();

	FileDialogs::SetDeafultHWND(hWnd);


	// setup the objects
	FreeCameraObject* freeCam = new FreeCameraObject(width, height);  
	freeCam->GetTransform()->Position = { 0.0f, 30.0f, -30.0f };
	freeCam->GetTransform()->Rotate(50.0f, 0.0f, 0.0f);
	GameObjectManager::GetInstance()->AddRootObject(freeCam); 






	/*PhysicsObject* phy1 = new PhysicsObject(EPrimitiveMeshTypes::Plane); 
	phy1->GetTransform()->Position = Vector3(0.0f, -20.0f, 0.0f);
	phy1->GetTransform()->LocalScale = Vector3(7.0f, 1.0f, 7.0f);
	GameObjectManager::GetInstance()->AddRootObject(phy1);  
	phy1->GetRB()->BodyType = rp3d::BodyType::STATIC;  

	PhysicsObject* phy2 = new PhysicsObject(EPrimitiveMeshTypes::Sphere);
	phy2->GetTransform()->Position = Vector3(0.0f, -20.0f, 0.0f);
	phy2->GetTransform()->LocalScale = Vector3(7.0f, 1.0f, 7.0f);
	GameObjectManager::GetInstance()->AddRootObject(phy2);
	phy2->GetRB()->BodyType = rp3d::BodyType::STATIC;

	CapsuleObject* cap = new CapsuleObject();
	cap->GetTransform()->Position = Vector3(0.0f, -15.0f, 0.0f);
	GameObjectManager::GetInstance()->AddRootObject(cap);

	std::vector<AGameObject*> objsList; 
	int rowSize = 30; int colSize = 20; 
	float rowSpacing = 5.f; float colSpacing = 5.f; 
	int sphereNum = 0, capsuleNum = 0, planeNum = 0, cubeNum = 0; 

	for (int i = 0; i < colSize; i++) 
	{
		for (int j = 0; j < rowSize; j++) 
		{
			int randNum = rand() % 4; 
			AGameObject* randObj = nullptr; 

			switch (randNum)
			{
			case 0:
			{ randObj = new SphereObject("Sphere" + std::to_string(sphereNum)); sphereNum++; break; }
			case 1:
			{ randObj = new CapsuleObject("Capsule" + std::to_string(capsuleNum)); capsuleNum++; break; }
			case 2:
			{ randObj = new PlaneObject("Plane" + std::to_string(planeNum)); planeNum++; break; }
			case 3:
			default:
			{ randObj = new CubeObject("Cube" + std::to_string(cubeNum)); cubeNum++; break; }
			}

			float x = j * rowSpacing - (rowSize / 2.f - 0.5f) * rowSpacing;
			float z = i * colSpacing - (colSize / 2.f - 0.5f) * colSpacing;
			randObj->GetTransform()->Position = { x , 0, z };

			randNum = (i == 0) ? rowSize * 4 : rand() % rowSize * 4 + 1;
			int parentIndex = (randNum / 4) + (i - 1) * rowSize;
			if (randNum == rowSize * 4) GameObjectManager::GetInstance()->AddRootObject(randObj);
			else objsList[parentIndex]->AttachChild(randObj);

			objsList.push_back(randObj);
		}
	}*/
}

void GameEngineWindow::OnUpdate()
{
	swapChain->ClearBuffer(0.0f, 0.0f, 0.0f);

	accumulator += (float)EngineTime::GetDeltaTime();
	float secsPerFrame = 1.f / (float)fps;
	while (accumulator >= secsPerFrame)
	{
		accumulator -= secsPerFrame;
		GameObjectManager::GetInstance()->UpdateEditor(secsPerFrame);

		if (EditorBackend::get()->getState() == EditorBackend::PLAY)
		{
			GameObjectManager::GetInstance()->UpdateGame(secsPerFrame);
			PhysicsEngine::GetInstance()->UpdateWorld(secsPerFrame);
			float factor = accumulator / secsPerFrame;
			PhysicsEngine::GetInstance()->UpdateRigidBodies(factor);
		}
		else if (EditorBackend::get()->getState() == EditorBackend::PAUSE)
		{
			if (EditorBackend::get()->getIsFrameStep())
			{
				GameObjectManager::GetInstance()->UpdateGame(secsPerFrame);
				PhysicsEngine::GetInstance()->UpdateWorld(secsPerFrame);
				float factor = accumulator / secsPerFrame;
				PhysicsEngine::GetInstance()->UpdateRigidBodies(factor);
				EditorBackend::get()->endFrameStep();
			}
		}
		else if (EditorBackend::get()->getState() == EditorBackend::EDIT)
		{
			int CTRL_Y = 89;
			int CTRL_Z = 90;
			int KEY_DELETE = 46;

			if (Keyboard::IsKeyPressed(CTRL_Z)) {
				EditorActionHistory::get()->Undo();
			}
			else if (Keyboard::IsKeyPressed(CTRL_Y)) {
				EditorActionHistory::get()->Redo();
			}
		}

		Keyboard::FlushCharBuffer();
	}
	

	GameObjectManager::GetInstance()->Draw(); 
	EditorGUIManager::GetInstance()->Render();
	swapChain->Present(true); 

	Keyboard::FlushEventsBuffer(); 
	Mouse::FlushEventsBuffer(); 
}

void GameEngineWindow::OnDestroy() 
{ 
	Window::OnDestroy();

	GameObjectManager::Destroy();
	EditorGUIManager::Destroy(); 
	GraphicsEngine::GetInstance()->Release();
	PhysicsEngine::GetInstance()->Release();
	Debug::destroy();
	EditorBackend::destroy();
	EditorActionHistory::destroy();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT GameEngineWindow::HandleWindowMessages(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) 
	{ 
		return true; 
	}

	return Window::HandleWindowMessages(hWnd, msg, wParam, lParam);
}
