#pragma once
#include <d3d11.h>



class SwapChain;
class DeviceContext;
class VertexBuffer;

class GraphicsEngine
{
public:
	static GraphicsEngine* GetInstance();
	GraphicsEngine(const GraphicsEngine&) = delete;
	GraphicsEngine& operator=(const GraphicsEngine&) = delete;

	bool Init();
	bool Release();

	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();
	VertexBuffer* CreateVertexBuffer();

	bool CreateShaders();
	bool SetShaders();
	void GetShaderBufferAndSize(void** bytecode, UINT* size);


private:
	GraphicsEngine() {};
	~GraphicsEngine() {};

private:
	static GraphicsEngine* sharedInstance;

	ID3D11Device* d3dDevice;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11DeviceContext* d3d11ImmContext;
	DeviceContext* immDeviceContext;

	IDXGIDevice* dxgiDevice;
	IDXGIAdapter* dxgiAdapter;
	IDXGIFactory* dxgiFactory;

	ID3DBlob* vsBlob = nullptr;
	ID3DBlob* psBlob = nullptr;
	ID3D11VertexShader* vShader = nullptr;
	ID3D11PixelShader* pShader = nullptr;

	friend class SwapChain;
	friend class VertexBuffer;
};