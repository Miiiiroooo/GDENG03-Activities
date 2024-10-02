#include "GameEngineWindow.h"
#include "EmptyGameObject.h"
#include "MeshRenderer.h"
#include "GameObjectManager.h"


GameEngineWindow::GameEngineWindow()
{
	windowClassName = "GameEngineClass";
}

GameEngineWindow::~GameEngineWindow()
{ 

}

void GameEngineWindow::OnCreate(HWND hWnd)
{
	// initialize graphics
	GraphicsEngine::GetInstance()->Init();
	GraphicsEngine::GetInstance()->SetViewport(windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);

	// setup the objects
	EmptyGameObject* empty1 = new EmptyGameObject("temp1");
	Transform* transform1 = empty1->GetTransform(); 
	transform1->Position = { -0.5f,  0.5f,  0.0f }; 
	transform1->Scale = { 0.5f,  0.5f,  1.0f };
	GameObjectManager::GetInstance()->AddObject(empty1);

	MeshRenderer* renderer1 = new MeshRenderer(L"DefaultShader");
	renderer1->Temp({
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		});
	empty1->AttachComponent(renderer1);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer1); 

	EmptyGameObject* empty2 = new EmptyGameObject("temp2");
	Transform* transform2 = empty2->GetTransform(); 
	transform2->Position = { 0.5f,  0.5f,  0.0f }; 
	transform2->Scale = { 0.5f,  0.5f,  1.0f }; 
	GameObjectManager::GetInstance()->AddObject(empty2); 

	MeshRenderer* renderer2 = new MeshRenderer(L"DefaultShader"); 
	renderer2->Temp({ 
		{0.0f, 0.0f, 1.0f},
		{0.2f, 0.6f, 1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.2f, 0.6f, 1.0f},
		});
	empty2->AttachComponent(renderer2);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer2); 

	EmptyGameObject* empty3 = new EmptyGameObject("temp3"); 
	Transform* transform3 = empty3->GetTransform(); 
	transform3->Position = { 0.0f,  -0.35f,  0.0f }; 
	transform3->Scale = { 1.0f,  1.0f,  1.0f }; 
	GameObjectManager::GetInstance()->AddObject(empty3); 

	MeshRenderer* renderer3 = new MeshRenderer(L"DefaultShader");
	renderer3->Temp({
		{0.6f, 0.8f, 1.0f},
		{0.0f, 0.4f, 0.6f},
		{0.0f, 0.4f, 0.6f},
		{0.6f, 0.8f, 1.0f},
		});
	empty3->AttachComponent(renderer3);
	GameObjectManager::GetInstance()->BindRendererToShader(renderer3); 
	
	// initialize swap chain
	swapChain = GraphicsEngine::GetInstance()->CreateSwapChain(hWnd, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top);
}

void GameEngineWindow::OnUpdate()
{
	swapChain->ClearBuffer(0.0f, 0.4f, 0.6f);

	//GameObjectManager::GetInstance()->ProcessInputs();
	//GameObjectManager::GetInstance()->Update();
	GameObjectManager::GetInstance()->Draw();

	swapChain->Present(true);
}

void GameEngineWindow::OnDestroy()
{
	Window::OnDestroy();

	GraphicsEngine::GetInstance()->Release();
}