#include "FreeCameraScript.h"
#include "../../../WindowSystem/Keyboard.h"
#include "../../../WindowSystem/Mouse.h"
#include "../Transform.h"


FreeCameraScript::FreeCameraScript(int width, int height) : AComponent("FreeCamera", EComponentTypes::Script)
{
	oldMousePos = { -1, -1 };
	currMousePos = { -1, -1 };

	yawRotationRate = 180.f / ((float)width * 1.05f); 
	pitchRotationRate = 90.f / ((float)height * 1.15f); 
}

FreeCameraScript::~FreeCameraScript() 
{

}

void FreeCameraScript::Clone(AComponent* copy)
{
	FreeCameraScript* copyCamera = (FreeCameraScript*)copy; 
	if (copyCamera == nullptr) return;

	oldMousePos = copyCamera->oldMousePos; 
	transform->Clone(copyCamera->transform);
}

void FreeCameraScript::Perform()
{
	if (Mouse::GetInstance()->IsButtonDown(Mouse::EMouseButtons::Right))
	{
		HandleMovement(); 
		HandleLookRotation();
	}
	else
	{
		HandleWheelInputs();

		oldMousePos = { -1, -1 };
		currMousePos = { -1, -1 };
	}
}

void FreeCameraScript::HandleMovement()
{
	Vector3 total = Vector3::Zero;
	if (Keyboard::GetInstance()->IsKeyDown('W')) total += transform->GetLocalForward();
	if (Keyboard::GetInstance()->IsKeyDown('S')) total -= transform->GetLocalForward();
	if (Keyboard::GetInstance()->IsKeyDown('A')) total -= transform->GetLocalRight(); 
	if (Keyboard::GetInstance()->IsKeyDown('D')) total += transform->GetLocalRight(); 
	if (Keyboard::GetInstance()->IsKeyDown('E')) total += Vector3::Up; 
	if (Keyboard::GetInstance()->IsKeyDown('Q')) total -= Vector3::Up; 
	total.Normalize();
	total *= movementSpeed * dt; 

	if (Keyboard::GetInstance()->IsKeyDown(VK_SHIFT)) total *= boostSpeed;

	transform->Position += total;
}

void FreeCameraScript::HandleLookRotation()
{
	oldMousePos = currMousePos;
	currMousePos = Mouse::GetInstance()->GetMousePos();

	if (oldMousePos.x == -1 && oldMousePos.y == -1) return;

	Vector2 dir = currMousePos - oldMousePos;

	float x = dir.y * pitchRotationRate;
	if (x + transform->GetEulerAngles().x > 65 || x + transform->GetEulerAngles().x < -65) x = 0;
	transform->Rotate(transform->GetLocalRight(), x);

	float y = dir.x * yawRotationRate;
	transform->Rotate(Vector3::Up, y); 
}

void FreeCameraScript::HandleWheelInputs()
{
	int rot = Mouse::GetInstance()->GetMouseWheelRotations();
	transform->Position += transform->GetLocalForward() * longitudinalStepDistance * rot;
}