#pragma once
#include "AMesh.h"
#include "../MathUtils.h"


template <typename T>
class PlaneMesh : public AMesh<T>
{
public:
	VertexBuffer<T>* CreateVertexBuffer(bool isRainbowed) override
	{
		std::vector<T> vertices(4);
		vertices[0].pos = { -2.5f, 0.0f,  2.5f };
		vertices[1].pos = {  2.5f, 0.0f,  2.5f };
		vertices[2].pos = { -2.5f, 0.0f, -2.5f };
		vertices[3].pos = {  2.5f, 0.0f, -2.5f };

		for (int i = 0; i < 4; i++)
		{
			vertices[i].vColor = (isRainbowed) ?
				Vector3(MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange()) :
				this->color;
		}

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), vertices);
	}

	IndexBuffer* CreateIndexBuffer() override
	{
		std::vector<unsigned short> indices = {
			0, 1, 2,
			1, 3, 2
		};
		return new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	}
};