#include "VertexBuffer.h"
#include "GraphicsEngine.h"



VertexBuffer::VertexBuffer() : buffer(0), inputLayout(0)
{

}

VertexBuffer::~VertexBuffer()
{

}

bool VertexBuffer::Load(void* verticesList, UINT vertexSize, UINT listSize, void* shaderCodeInBytes, UINT shaderCodeSize)
{
	if (inputLayout) inputLayout->Release();
	if (buffer) buffer->Release();

	this->vertexSize = vertexSize;
	this->listSize = listSize;

	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = vertexSize * listSize;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA srData;
	srData.pSysMem = verticesList;

	if (FAILED(GraphicsEngine::GetInstance()->d3dDevice->CreateBuffer(&desc, &srData, &buffer))) return false;

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		//SEMANTIC NAME - SEMANTIC INDEX  -   FORMAT   -    INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION",          0,    DXGI_FORMAT_R32G32B32_FLOAT,  0,           0,       D3D11_INPUT_PER_VERTEX_DATA,   0},
		{"COLOR",             0,    DXGI_FORMAT_R32G32B32_FLOAT,  0,    D3D11_APPEND_ALIGNED_ELEMENT,       D3D11_INPUT_PER_VERTEX_DATA,   0}
	};

	UINT layoutSize = ARRAYSIZE(layout);

	if (FAILED(GraphicsEngine::GetInstance()->d3dDevice->CreateInputLayout(layout, layoutSize, shaderCodeInBytes, shaderCodeSize, &inputLayout))) return false;

	return true;
}

UINT VertexBuffer::GetSizeVertexList()
{
	return listSize;
}

bool VertexBuffer::Release()
{
	if (this == nullptr) return false;

	inputLayout->Release();
	buffer->Release();
	delete this;
	return true;
}
