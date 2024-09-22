#pragma once
#include "VertexBuffer.h"
#include "Vector3.h"



class DeviceContext;

class Quad
{
public:
	Quad(Vector3 topLeft, Vector3 topRight, Vector3 bottomLeft, Vector3 bottomRight);
	Quad(VertexData topLeft, VertexData topRight, VertexData bottomLeft, VertexData bottomRight);
	~Quad();

	UINT GetStrides();
	UINT GetVertexCount();
	UINT GetStartVertex();

	void Load(void* shaderCodeInBytes, UINT shaderCodeSize);
	void Draw();



private:
	Vector3 vertexPosList[4];
	VertexData vertexList[4];
	bool hasData;

	UINT vertexCount;
	UINT startVertex;

	VertexBuffer* quad;

	friend class DeviceContext;
};

