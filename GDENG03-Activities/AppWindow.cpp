#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector3.h"
#include <string>



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

	/*VertexData list[] = {
		VertexData({ { 0.0f, -0.25f, 1.0f}, {1.0f, 0.0f, 0.0f} }),
		VertexData({ { 0.5f, -0.75f, 1.0f},{0.0f, 1.0f, 0.0f} }),
		VertexData({ {-0.5f, -0.75f, 1.0f},{0.0f, 0.0f, 1.0f} })
	};
	UINT listSize = ARRAYSIZE(list);*/


	void* shaderCodeInBytes = nullptr;
	UINT shaderCodeSize = 0;
	GraphicsEngine::GetInstance()->CreateShaders();
	GraphicsEngine::GetInstance()->GetShaderBufferAndSize(&shaderCodeInBytes, &shaderCodeSize);

	/*vertexBuffer1 = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	vertexBuffer1->Load(list, sizeof(VertexData), listSize, shaderCodeInBytes, shaderCodeSize);*/
	/*vertexBuffer2 = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	vertexBuffer2->Load(list2, sizeof(Vector3), listSize, shaderCodeInBytes, shaderCodeSize);*/

	VertexData v1;
	v1.pos = Vector3({ -0.5f,  0.5f, 0.0f });
	v1.pp = Vector3({ 0.0f,  0.75f, 0.0f });
	v1.vColor = Vector3({ 1.0f, 0.0f, 0.0f });
	v1.cc = Vector3({ 0.0f, 0.0f, 1.0f });
	VertexData v2;
	v2.pos = Vector3({ 0.5f,  0.5f, 0.0f });
	v2.pp = Vector3({ 0.75f,   0.0f, 0.0f });
	v2.vColor = Vector3({ 0.0f, 1.0f, 0.0f });
	v2.cc = Vector3({ 0.0f, 1.0f, 1.0f });
	VertexData v3;
	v3.pos = Vector3({ -0.5f, -0.5f, 0.0f });
	v3.pp = Vector3({ -0.75f,   0.0f, 0.0f });
	v3.vColor = Vector3({ 1.0f, 0.0f, 0.0f });
	v3.cc = Vector3({ 0.0f, 0.0f, 1.0f });
	VertexData v4;
	v4.pos = Vector3({ 0.5f, -0.5f, 0.0f });
	v4.pp = Vector3({ 0.0f, -0.75f, 0.0f });
	v4.vColor = Vector3({ 0.0f, 1.0f, 0.0f });
	v4.cc = Vector3({ 0.0f, 1.0f, 1.0f });

	quad1 = new Quad(v1, v2, v3, v4);
	quad1->Load(shaderCodeInBytes, shaderCodeSize);

	/*quad2 = new Quad(VertexData({ {-0.5f,  0.5f, 0.0f}, { 0.0f,  0.75f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} }),
		VertexData({ { 0.5f,  0.5f, 0.0f},{ 0.75f,   0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f, 1.0f} }),
		VertexData({ {-0.5f, -0.5f, 0.0f},{-0.75f,   0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f} }),
		VertexData({ { 0.5f, -0.5f, 0.0f},{  0.0f, -0.75f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f} }));
	quad2->Load(shaderCodeInBytes, shaderCodeSize);*/ 
	 
	//quad3 = new Quad(Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.5f, -0.5f, 0.0f), Vector3(-0.5f, -1.0f, 0.0f), Vector3(0.5f, -1.0f, 0.0f));
	//quad3->Load(shaderCodeInBytes, shaderCodeSize);

	ConstantData cc;
	cc.m_angle = -90;

	cBuffer = GraphicsEngine::GetInstance()->CreateConstantBuffer();
	cBuffer->Init(&cc, sizeof(ConstantData));
}

void AppWindow::OnUpdate()
{
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(swapChain, 0, 0.4, 0.6, 1);

	RECT rc = GetClientWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::GetInstance()->SetShaders();

	/*GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(vertexBuffer1);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTrianglesList(vertexBuffer1->GetSizeVertexList(), 0);*/
	/*GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(vertexBuffer2);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTrianglesList(vertexBuffer2->GetSizeVertexList(), 0);*/
	
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawQuad(quad1); 
	//GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawQuad(quad2); 
	//GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawQuad(quad3);

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f * m_delta_time;
	ConstantData cc;
	cc.m_angle = m_angle; 

	cBuffer->Update(GraphicsEngine::GetInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(cBuffer);

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