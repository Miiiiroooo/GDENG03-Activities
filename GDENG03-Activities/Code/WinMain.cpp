#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/GameObjects/EmptyGameObject.h"


std::string Print(DirectX::XMFLOAT3 value)
{
	return std::to_string(value.x) + " " + std::to_string(value.y) + " " + std::to_string(value.z);
}

void ForTesting()
{
	EmptyGameObject* e1 = new EmptyGameObject("e1"); 
	Transform* transform1 = e1->GetTransform(); 
	transform1->LocalScale = { 2.0f,  2.0f,  2.0f };

	EmptyGameObject* e2 = new EmptyGameObject("e2");
	e1->AttachChild(e2); 
	Transform* transform2 = e2->GetTransform(); 
	transform2->LocalScale = { 0.75f, 0.75f, 0.75f };

	EmptyGameObject* e3 = new EmptyGameObject("e3"); 
	e2->AttachChild(e3); 
	Transform* transform3 = e3->GetTransform(); 
	transform3->LocalScale = { 0.75f, 0.75f, 0.75f };

	std::string to_print = "Awake   e1 " + Print(transform1->LocalScale) + " " + Print(transform1->Position) + "\n";
	OutputDebugString(to_print.c_str()); 
	to_print = "Awake   e2 " + Print(transform2->LocalScale) + " " + Print(transform2->Position) + "\n";
	OutputDebugString(to_print.c_str()); 
	to_print = "Awake   e3 " + Print(transform3->LocalScale) + " " + Print(transform3->Position) + "\n\n";
	OutputDebugString(to_print.c_str()); 

	transform3->LocalScale = { 2.0f, 0.75f, 0.75f };

	to_print = "Start   e1 " + Print(transform1->LocalScale) + " " + Print(transform1->Position) + "\n";
	OutputDebugString(to_print.c_str()); 
	to_print = "Start   e2 " + Print(transform2->LocalScale) + " " + Print(transform2->Position) + "\n";
	OutputDebugString(to_print.c_str()); 
	to_print = "Start   e3 " + Print(transform3->LocalScale) + " " + Print(transform3->Position) + "\n\n";
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