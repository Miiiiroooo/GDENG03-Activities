#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"


struct Vector3
{
	float x, y, z;
};



AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::OnCreate()
{
	GraphicsEngine::GetInstance()->Init();
	swapChain = GraphicsEngine::GetInstance()->CreateSwapChain();

	RECT rc = GetClientWindowRect();
	bool res = swapChain->Init(hWnd, rc.right - rc.left, rc.bottom - rc.top);

	Vector3 list[] = {
		{-0.5f, -0.5f, 0.0f},
		{ 0.0f,  0.5f, 0.0f},
		{ 0.5f, -0.5f, 0.0f}
	};
	UINT listSize = ARRAYSIZE(list);


	void* shaderCodeInBytes = nullptr;
	UINT shaderCodeSize = 0;
	GraphicsEngine::GetInstance()->CreateShaders();
	GraphicsEngine::GetInstance()->GetShaderBufferAndSize(&shaderCodeInBytes, &shaderCodeSize);

	vertexBuffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	vertexBuffer->Load(list, sizeof(Vector3), listSize, shaderCodeInBytes, shaderCodeSize);
}

void AppWindow::OnUpdate()
{
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(swapChain, 0, 0.4, 0.6, 1);

	RECT rc = GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::GetInstance()->SetShaders();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(vertexBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTrianglesList(vertexBuffer->GetSizeVertexList(), 0);

	swapChain->Present(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	swapChain->Release();
	vertexBuffer->Release();
	GraphicsEngine::GetInstance()->Release();
}