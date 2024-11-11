#pragma once
#include "AMesh.h"
#include "../MathUtils.h"


template <typename T>
class QuadMesh : public AMesh<T>
{
public:
	VertexBuffer<T>* CreateVertexBuffer(bool isRainbowed) override
	{
		std::vector<T> vertices(4); 
		vertices[0].pos = { -0.5f,  0.5f, 0.0f };
		vertices[1].pos = { 0.5f,  0.5f, 0.0f };
		vertices[2].pos = { -0.5f, -0.5f, 0.0f };
		vertices[3].pos = { 0.5f, -0.5f, 0.0f };
		vertices[0].vColor = { 1.0f, 1.0f, 1.0f };
		vertices[1].vColor = { 1.0f, 1.0f, 1.0f };
		vertices[2].vColor = { 1.0f, 1.0f, 1.0f };
		vertices[3].vColor = { 1.0f, 1.0f, 1.0f };

		for (int i = 0; i < 4; i++)
		{
			vertices[i].vColor = (isRainbowed) ?
				Vector3(MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange()) :
				this->color;
		}

		/*std::vector<T> data = {
			{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		};*/

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