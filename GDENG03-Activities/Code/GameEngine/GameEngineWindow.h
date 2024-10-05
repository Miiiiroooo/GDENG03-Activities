#pragma once
#include "../WindowSystem/Window.h"
#include "../DirectXClasses/SwapChain.h"
#include "Components/Renderer/MeshRenderer.h"
#include "../DirectXClasses/Buffers/BufferDataTypes.h"


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

	float totalAngleAnimation = -90;
	float totalAngleTimeScale = -30;
	float animSpeed = 15;
	float timeScaleSpeed = 30;

	VertexConstantBuffer<TempConstant>* vConstant;
	PixelConstantBuffer<TempConstant>* pConstant;
};