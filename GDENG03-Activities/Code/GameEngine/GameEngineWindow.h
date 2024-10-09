#pragma once
#include "../WindowSystem/Window.h"
#include "../DirectXClasses/SwapChain.h"
#include "Components/Transform.h"


class GameEngineWindow : public Window
{
public:
	GameEngineWindow();
	~GameEngineWindow();

protected:
	void OnCreate(HWND hWnd) override;
	void OnUpdate() override;
	void OnDestroy() override;
	LRESULT CALLBACK HandleWindowMessages(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;


private:
	SwapChain* swapChain;

	float rSpeed = 20;
	Transform* t1;
	Transform* t2;
	Transform* t3;
};