#pragma once
#include "DirectXClasses/Buffers/VertexBuffer.cpp"
#include "DirectXClasses/Buffers/IndexBuffer.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;


template <typename T>
class AMesh
{
public:
	virtual VertexBuffer<T>* CreateVertexBuffer(bool isRainbowed) = 0;
	virtual IndexBuffer* CreateIndexBuffer() = 0;
	void SetColor(Vector3 color) { this->color = color; };


protected:
	Vector3 color = Vector3::One;
};