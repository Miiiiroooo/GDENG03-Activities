#include "GameEngineWindow.h"
#include "EngineTime.h"
#include "Managers/GameObjectManager.h"
#include "GameObjects/EmptyGameObject.h"
#include <math.h>


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


	// Temp
	vConstant = new VertexConstantBuffer<TempConstant>(GraphicsEngine::GetInstance(), 1u);
	vConstant->Init();
	pConstant = new PixelConstantBuffer<TempConstant>(GraphicsEngine::GetInstance(), 0u);
	pConstant->Init();


	// SLIDE 13
	EmptyGameObject* empty1 = new EmptyGameObject("temp1");
	Transform* transform1 = empty1->GetTransform(); 
	GameObjectManager::GetInstance()->AddObject(empty1);

	MeshRenderer* renderer1 = new MeshRenderer(L"DefaultShader");
	renderer1->TempAnimation(1);
	empty1->AttachComponent(renderer1);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer1); 


	// SLIDE 14
	/*EmptyGameObject* empty2 = new EmptyGameObject("temp2"); 
	Transform* transform2 = empty2->GetTransform(); 
	GameObjectManager::GetInstance()->AddObject(empty2); 

	MeshRenderer* renderer2 = new MeshRenderer(L"DefaultShader"); 
	renderer2->TempAnimation(2); 
	empty2->AttachComponent(renderer2); 
	GameObjectManager::GetInstance()->BindRendererToShader(renderer2); */
}

void GameEngineWindow::OnUpdate()
{
	// SLIDE 13
	animSpeed = 15;
	totalAngleAnimation += animSpeed * EngineTime::GetDeltaTime();
	totalAngleTimeScale += timeScaleSpeed * EngineTime::GetFixedDeltaTime();

	float newScale = (std::sin(totalAngleTimeScale * M_PI / 180.f)  + 1.0f) * (35.0f / 2.0f); // clamp between 0 and 35
	EngineTime::SetTimeScale(newScale);

	TempConstant cc;
	cc.m_angle = totalAngleAnimation * M_PI / 180.f;


	// SLIDE 14
	/*animSpeed = 60;
	totalAngleAnimation += animSpeed * EngineTime::GetDeltaTime(); 

	TempConstant cc; 
	cc.m_angle = totalAngleAnimation * M_PI / 180.f; */



	vConstant->SetConstants(cc);
	vConstant->BindToPipeline();
	pConstant->SetConstants(cc);
	pConstant->BindToPipeline();




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
