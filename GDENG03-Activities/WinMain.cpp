#include "GameEngineWindow.h"
#include "Transform.h"
#include "EmptyGameObject.h"


std::string Print(DirectX::XMFLOAT3 value)
{
	return std::to_string(value.x) + " " + std::to_string(value.y) + " " + std::to_string(value.z);
}

void ForTesting()
{
	EmptyGameObject* e1 = new EmptyGameObject("e1"); 
	Transform* transform1 = e1->GetTransform(); 
	transform1->Position = { 1.0f,  0.0f,  0.0f };

	EmptyGameObject* e2 = new EmptyGameObject("e2");
	e1->AttachChild(e2); 
	Transform* transform2 = e2->GetTransform(); 
	transform2->Position = { -1.0f,  0.0f,  0.0f };

	EmptyGameObject* e3 = new EmptyGameObject("e3"); 
	e2->AttachChild(e3); 
	Transform* transform3 = e3->GetTransform(); 
	transform3->Position = { 3.0f,  0.0f,  0.0f }; 

	std::string to_print = "Awake   e1 " + Print(transform1->Position) + " " + Print(transform1->LocalPosition) + "\n"; 
	OutputDebugString(to_print.c_str()); 
	to_print = "Awake   e2 " + Print(transform2->Position) + " " + Print(transform2->LocalPosition) + "\n"; 
	OutputDebugString(to_print.c_str()); 
	to_print = "Awake   e3 " + Print(transform3->Position) + " " + Print(transform3->LocalPosition) + "\n\n"; 
	OutputDebugString(to_print.c_str()); 

	transform1->Position = { -5.0f, 0.0f, 0.0f }; 

	to_print = "Start   e1 " + Print(transform1->Position) + " " + Print(transform1->LocalPosition) + "\n"; 
	OutputDebugString(to_print.c_str()); 
	to_print = "Start   e2 " + Print(transform2->Position) + " " + Print(transform2->LocalPosition) + "\n"; 
	OutputDebugString(to_print.c_str()); 
	to_print = "Start   e3 " + Print(transform3->Position) + " " + Print(transform3->LocalPosition) + "\n\n"; 
	OutputDebugString(to_print.c_str()); 
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ForTesting();



	GameEngineWindow gameEngine;

	if (gameEngine.Init(640, 480, "Aamir Akim"))
	{
		while (gameEngine.IsRunning())
		{
			gameEngine.Update();
		}
	}

	gameEngine.Release();

	return 0;
}