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
	transform1->Position = { 1.0f,  0.0f,  0.0f };
	//transform1->Rotate(Vector3(0, 1, 0), 30);
	//transform1->Rotate(Vector3(1, 0, 0), 270);

	EmptyGameObject* e2 = new EmptyGameObject("e2");
	e1->AttachChild(e2);
	Transform* transform2 = e2->GetTransform();
	transform2->Position = { -1.0f,  0.0f,  0.0f };
	transform2->Rotate(30, 0, 0);

	EmptyGameObject* e3 = new EmptyGameObject("e3");
	Transform* transform3 = e3->GetTransform();
	transform3->Position = { 3.0f,  0.0f,  0.0f };
	e2->AttachChild(e3);



	std::string to_print = "Awake   e1 " + Print(transform1->GetEulerAngles()) + " " + Print(transform1->GetLocalEulerAngles()) + "\n";
	OutputDebugString(to_print.c_str());
	to_print = "Awake   e2 " + Print(transform2->GetEulerAngles()) + " " + Print(transform2->GetLocalEulerAngles()) + "\n";
	OutputDebugString(to_print.c_str());
	to_print = "Awake   e3 " + Print(transform3->Position) + " " + Print(transform3->LocalPosition) + "\n\n";
	OutputDebugString(to_print.c_str());

	transform1->Position = { -5.0f, 0.0f, 0.0f };
	transform1->Rotate(0, 30, 0);

	to_print = "Start   e1 " + Print(transform1->GetEulerAngles()) + " " + Print(transform1->GetLocalEulerAngles()) + "\n";
	OutputDebugString(to_print.c_str());
	to_print = "Start   e2 " + Print(transform2->GetEulerAngles()) + " " + Print(transform2->GetLocalEulerAngles()) + "\n";
	OutputDebugString(to_print.c_str());
	to_print = "Start   e3 " + Print(transform3->Position) + " " + Print(transform3->LocalPosition) + "\n\n";
	OutputDebugString(to_print.c_str());
}

#include <GeometricPrimitive.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ForTesting();


	float size = 8.f;
	Vector2 dir = Vector2::UnitY;
	float currAngle = 0;
	float angleIncrements = 360.f / size - 1.f;

	for (int i = 1; i < size; i++)
	{
		dir.x = sin(currAngle * M_PI / 180.f) / 2.f;
		dir.y = cos(currAngle * M_PI / 180.f) / 2.f;
		Vector3 newVert = Vector3(dir.x, dir.y, 0.0f);
		currAngle += angleIncrements;

		int temp = 0;
	}


	GameEngineWindow gameEngine;  

	if (gameEngine.Init(1024, 768, "Aamir Akim"))  
	{
		while (gameEngine.IsRunning())  
		{
			gameEngine.Update();  
		}
	}

	gameEngine.Release();  

	return 0;
}