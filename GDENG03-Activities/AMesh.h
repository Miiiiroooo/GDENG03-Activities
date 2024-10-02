#pragma once
#include "VertexBuffer.cpp"
#include "IndexBuffer.h"


template <typename T>
class AMesh
{
public:
	virtual VertexBuffer<T>* CreateVertexBuffer() = 0;
	virtual IndexBuffer* CreateIndexBuffer() = 0;
};