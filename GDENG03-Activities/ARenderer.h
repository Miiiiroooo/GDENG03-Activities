#pragma once
#include <vector>
#include <string>
#include "AComponent.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.cpp"
#include "BufferDataTypes.h"


class ARenderer : public AComponent
{
public:
	ARenderer(std::string compoonentName, LPCWSTR shaderType);
	~ARenderer();

	virtual bool Release();
	void Perform() override;
	LPCWSTR GetShaderType();

protected:
	void InitRenderer();


protected:
	LPCWSTR shaderType;
	D3D11_PRIMITIVE_TOPOLOGY topologyType;

	std::vector<AD3D11Object*> bufferList;
	IndexBuffer* indexBuffer;
	VertexConstantBuffer<TMatrix>* vConstantBuffer;
};