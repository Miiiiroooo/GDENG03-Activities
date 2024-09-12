#pragma once
#include <d3d11.h>



class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool Init(HWND hWnd, UINT width, UINT height);
	bool Release();

	bool Present(bool vSync);


private:
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* renderTargetView;

	friend class DeviceContext;
};