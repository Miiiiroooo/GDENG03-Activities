#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector3.h"



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

	//Vector3 list[] = {
	//	{0.25f, 0.75f, 1.0f},
	//	{0.75f, 0.75f, 1.0f},
	//	{0.25f, 0.25f, 1.0f}
	//};
	// 
	//Vector3 list2[] = {
	//	{ 1.0f, 1.0f, 0.0f},
	//	{ 1.0f,  0.0f, 0.0f},
	//	{ 0.0f,  0.0f, 0.0f}
	//};
	// 
	//UINT listSize = ARRAYSIZE(list1);

	VertexData list[] = {
		VertexData({ { 0.0f, -0.25f, 1.0f}, {1.0f, 0.0f, 0.0f} }),
		VertexData({ { 0.5f, -0.75f, 1.0f},{0.0f, 1.0f, 0.0f} }),
		VertexData({ {-0.5f, -0.75f, 1.0f},{0.0f, 0.0f, 1.0f} })
	};
	UINT listSize = ARRAYSIZE(list);


	void* shaderCodeInBytes = nullptr;
	UINT shaderCodeSize = 0;
	GraphicsEngine::GetInstance()->CreateShaders();
	GraphicsEngine::GetInstance()->GetShaderBufferAndSize(&shaderCodeInBytes, &shaderCodeSize);

	vertexBuffer1 = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	vertexBuffer1->Load(list, sizeof(VertexData), listSize, shaderCodeInBytes, shaderCodeSize);
	/*vertexBuffer2 = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	vertexBuffer2->Load(list2, sizeof(Vector3), listSize, shaderCodeInBytes, shaderCodeSize);*/

	quad1 = new Quad(VertexData({ {-0.75f, 0.75f, 0.0f}, {1.0f, 0.0f, 0.0f} }),
		VertexData({ {-0.25f, 0.75f, 0.0f},{0.0f, 1.0f, 0.0f} }),
		VertexData({ {-0.75f, 0.25f, 0.0f},{0.0f, 0.0f, 1.0f} }),
		VertexData({ {-0.25f, 0.25f, 0.0f},{1.0f, 1.0f, 0.0f} }));
	quad1->Load(shaderCodeInBytes, shaderCodeSize);

	quad2 = new Quad(VertexData({ {0.25f, 0.75f, 0.0f}, {0.0f, 1.0f, 0.0f} }),
		VertexData({ {0.75f, 0.75f, 0.0f},{0.0f, 1.0f, 0.0f} }),
		VertexData({ {0.25f, 0.25f, 0.0f},{0.0f, 1.0f, 0.0f} }),
		VertexData({ {0.75f, 0.25f, 0.0f},{0.0f, 1.0f, 0.0f} }));
	quad2->Load(shaderCodeInBytes, shaderCodeSize); 
	 
	//quad3 = new Quad(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(-0.5f, -1.0f, 0.0f), Vector3(0.5f, -1.0f, 0.0f));
	//quad3->Load(shaderCodeInBytes, shaderCodeSize);
}

void AppWindow::OnUpdate()
{
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(swapChain, 0, 0.4, 0.6, 1);

	RECT rc = GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::GetInstance()->SetShaders();

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(vertexBuffer1);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTrianglesList(vertexBuffer1->GetSizeVertexList(), 0);
	/*GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(vertexBuffer2);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTrianglesList(vertexBuffer2->GetSizeVertexList(), 0);*/
	
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawQuad(quad1); 
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawQuad(quad2); 
	//GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawQuad(quad3);

	swapChain->Present(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	swapChain->Release();
	vertexBuffer1->Release();
	vertexBuffer2->Release();
	GraphicsEngine::GetInstance()->Release();
}