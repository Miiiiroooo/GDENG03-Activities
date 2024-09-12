#pragma once
#include "Window.h"
#include "SwapChain.h"
#include "VertexBuffer.h"


class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	void OnCreate() override;
	void OnUpdate() override;
	void OnDestroy() override;


private:
	SwapChain* swapChain;
	VertexBuffer* vertexBuffer;
};