#pragma once
#include "AMesh.h"


template <typename T>
class CubeMesh : public AMesh<T>
{
public:
	VertexBuffer<T>* CreateVertexBuffer() override
	{

	}

	IndexBuffer* CreateIndexBuffer() override 
	{

	}
};