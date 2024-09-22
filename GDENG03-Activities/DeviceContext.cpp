#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"


DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) : deviceContext(deviceContext)
{

}

DeviceContext::~DeviceContext()
{

}

bool DeviceContext::Release()
{
	deviceContext->Release();
	delete this;
	return true;
}

void DeviceContext::ClearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a)
{
	FLOAT clearColor[] = { r,g,b,a };
	deviceContext->ClearRenderTargetView(swapChain->renderTargetView, clearColor);
	deviceContext->OMSetRenderTargets(1, &swapChain->renderTargetView, nullptr);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* buffer)
{
	UINT stride = buffer->vertexSize;
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &buffer->buffer, &stride, &offset);
	deviceContext->IASetInputLayout(buffer->inputLayout);
}

void DeviceContext::DrawTrianglesList(UINT vertexCount, UINT startIndex)
{
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->Draw(vertexCount, startIndex);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	deviceContext->RSSetViewports(1, &vp);
}

void DeviceContext::DrawQuad(Quad* quad)
{
	UINT stride = quad->GetStrides();
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &quad->quad->buffer, &stride, &offset);
	deviceContext->IASetInputLayout(quad->quad->inputLayout);

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	deviceContext->Draw(quad->GetVertexCount(), quad->GetStartVertex());
}
