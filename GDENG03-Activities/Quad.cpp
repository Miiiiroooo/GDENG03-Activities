#include "Quad.h"
#include "GraphicsEngine.h"

Quad::Quad(Vector3 topLeft, Vector3 topRight, Vector3 bottomLeft, Vector3 bottomRight) : hasData(false), vertexCount(4), startVertex(0)
{
	vertexPosList[0] = topLeft;
	vertexPosList[1] = topRight;
	vertexPosList[2] = bottomLeft;
	vertexPosList[3] = bottomRight;
}

Quad::Quad(VertexData topLeft, VertexData topRight, VertexData bottomLeft, VertexData bottomRight) : hasData(true), vertexCount(4), startVertex(0)
{
	vertexList[0] = topLeft;
	vertexList[1] = topRight;
	vertexList[2] = bottomLeft;
	vertexList[3] = bottomRight;
}

Quad::~Quad()
{
	quad->Release();
	delete this;
}

UINT Quad::GetStrides()
{
	return  hasData ? sizeof(VertexData) : sizeof(Vector3);
}

UINT Quad::GetVertexCount()
{
	return vertexCount;
}

UINT Quad::GetStartVertex()
{
	return startVertex;
}

void Quad::Load(void* shaderCodeInBytes, UINT shaderCodeSize)
{
	quad = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	quad->Load(hasData ? (void*)vertexList : (void*)vertexPosList, 
		hasData ? sizeof(VertexData) : sizeof(Vector3), 
		hasData ? ARRAYSIZE(vertexList) : ARRAYSIZE(vertexPosList),
		shaderCodeInBytes, 
		shaderCodeSize);
}

void Quad::Draw()
{

}