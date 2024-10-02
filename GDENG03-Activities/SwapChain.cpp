#include "SwapChain.h"
#include "GraphicsEngine.h"


SwapChain::SwapChain(GraphicsEngine* gfx) : gfx (gfx)
{

}

SwapChain::~SwapChain()
{

}

bool SwapChain::Init(HWND hWnd, UINT width, UINT height)
{
	ID3D11Device* device = gfx->GetDevice();


	DXGI_SWAP_CHAIN_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hWnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	 
	HRESULT res = gfx->GetFactory()->CreateSwapChain(device, &desc, &swapChain);

	if (FAILED(res))
	{
		return false;
	}

	ID3D11Texture2D* buffer;
	res = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(res))
	{
		return false;
	}

	res = device->CreateRenderTargetView(buffer, nullptr, &renderTargetView); 
	buffer->Release();

	if (FAILED(res))
	{
		return false;
	}

	gfx->GetDeviceContext()->OMSetRenderTargets(1u, renderTargetView.GetAddressOf(), nullptr);

	return true;
}

bool SwapChain::Release()
{
	swapChain.Get()->Release();
	renderTargetView.Get()->Release();
	delete this;

	return true;
}

bool SwapChain::ClearBuffer(float r, float g, float b)
{
	if (renderTargetView.Get() == nullptr)
	{
		return false;
	}

	const float color[] = { r, g, b, 1.0f };
	gfx->GetDeviceContext()->ClearRenderTargetView(renderTargetView.Get(), color);
	//gfx->GetDeviceContext()->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);

	return true;
}

bool SwapChain::Present(bool vSync)
{
	swapChain->Present(vSync, 0);

	return true;
}
