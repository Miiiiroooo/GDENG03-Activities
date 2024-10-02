#pragma once
#include "Window.h"
#include "SwapChain.h"


class GameEngineWindow : public Window
{
public:
	GameEngineWindow();
	~GameEngineWindow();

protected:
	void OnCreate(HWND hWnd) override;
	void OnUpdate() override;
	void OnDestroy() override;


private:
	SwapChain* swapChain;
};

