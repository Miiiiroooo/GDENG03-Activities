#pragma once
#include "Window.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "Quad.h"


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
	VertexBuffer* vertexBuffer1;
	VertexBuffer* vertexBuffer2;
	ConstantBuffer* cBuffer;
	Quad* quad1;
	Quad* quad2;
	Quad* quad3;

	unsigned long m_old_time = 0;
	float m_delta_time = 0;
	float m_angle = -90;
};