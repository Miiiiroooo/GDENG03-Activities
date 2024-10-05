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





__declspec(align(16))
struct TempConstant
{
	float m_angle;
};

struct TempVertex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 vColor;
	DirectX::XMFLOAT3 pos1;
	DirectX::XMFLOAT3 vColor1;

	TempVertex() : pos(0.0f, 0.0f, 0.0f), vColor(0.0f, 0.0f, 0.0f), pos1(0.0f, 0.0f, 0.0f), vColor1(0.0f, 0.0f, 0.0f)
	{
	}

	TempVertex(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT3& vColor, const DirectX::XMFLOAT3& pos1, const DirectX::XMFLOAT3& vColor1) :
		pos(pos), vColor(vColor), pos1(pos1), vColor1(vColor1)
	{
	}

	TempVertex(const TempVertex& copy) : pos(copy.pos), vColor(copy.vColor), pos1(copy.pos1), vColor1(copy.vColor1)
	{
	}
};