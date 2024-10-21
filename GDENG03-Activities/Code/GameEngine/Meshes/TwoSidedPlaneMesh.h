#pragma once
#include "AMesh.h"


template <typename T>
class TwoSidedPlaneMesh : public AMesh<T>
{
public:
	VertexBuffer<T>* CreateVertexBuffer() override
	{
		std::vector<T> data(4);
		data[0].pos = { -2.5f, 0.0f,  2.5f };
		data[1].pos = { 2.5f, 0.0f,  2.5f };
		data[2].pos = { -2.5f, 0.0f, -2.5f };
		data[3].pos = { 2.5f, 0.0f, -2.5f };

		data[0].vColor = { 1.0f, 1.0f, 1.0f };
		data[1].vColor = { 1.0f, 1.0f, 1.0f };
		data[2].vColor = { 1.0f, 1.0f, 1.0f };
		data[3].vColor = { 1.0f, 1.0f, 1.0f };

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), data);
	}

	IndexBuffer* CreateIndexBuffer() override
	{
		std::vector<unsigned short> indices = {
			0, 1, 2,
			1, 3, 2,
			0, 2, 1,
			2, 3, 1
		};
		return new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	}
};