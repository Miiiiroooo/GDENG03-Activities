#pragma once
#include <d3d11.h>



class DeviceContext;

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool Load(void* verticesList, UINT vertexSize, UINT listSize, void* shaderCodeInBytes, UINT shaderCodeSize);
	UINT GetSizeVertexList();
	bool Release();


private:
	UINT vertexSize; 
	UINT listSize;
	ID3D11Buffer* buffer;
	ID3D11InputLayout* inputLayout;

	friend class DeviceContext;
};