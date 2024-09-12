#pragma once
#include <d3d11.h>


class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	~DeviceContext();

	bool Release();
	void ClearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* buffer);
	void DrawTrianglesList(UINT vertexCount, UINT startIndex);
	void SetViewportSize(UINT width, UINT height);


private:
	ID3D11DeviceContext* deviceContext;
};