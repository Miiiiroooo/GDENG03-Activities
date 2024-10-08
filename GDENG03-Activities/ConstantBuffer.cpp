#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"


ConstantBuffer::ConstantBuffer()
{

}

ConstantBuffer::~ConstantBuffer()
{

}

bool ConstantBuffer::Init(void* buffer, UINT size_buffer)
{
	if (m_buffer)m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(GraphicsEngine::GetInstance()->d3dDevice->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	return true;
}

void ConstantBuffer::Update(DeviceContext* context, void* buffer)
{
	context->deviceContext->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::Release()
{
	if (m_buffer)m_buffer->Release();
	delete this;
	return true;
}