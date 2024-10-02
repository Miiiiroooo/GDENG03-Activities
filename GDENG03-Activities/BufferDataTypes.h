#pragma once
#include <DirectXMath.h>


struct VertexData
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 vColor;

	VertexData() : pos(0.0f, 0.0f, 0.0f), vColor(0.0f, 0.0f, 0.0f)
	{
	}

	VertexData(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& vColor) : pos(pos), vColor(vColor)
	{
	}

	VertexData(const VertexData& copy) : pos(copy.pos), vColor(copy.vColor)
	{
	}
};


struct TMatrix
{
	DirectX::XMMATRIX transform;
};