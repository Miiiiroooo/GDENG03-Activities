#pragma once
#include "AMesh.h"


template <typename T>
class QuadMesh : public AMesh<T>
{
public:
	VertexBuffer<T>* CreateVertexBuffer() override
	{
		std::vector<T> data(4); 
		data[0].pos = { -0.5f,  0.5f, 0.0f };
		data[1].pos = { 0.5f,  0.5f, 0.0f };
		data[2].pos = { -0.5f, -0.5f, 0.0f };
		data[3].pos = { 0.5f, -0.5f, 0.0f };
		data[0].vColor = { 1.0f, 0.0f, 0.0f };
		data[1].vColor = { 0.0f, 1.0f, 0.0f };
		data[2].vColor = { 0.0f, 0.0f, 1.0f };
		data[3].vColor = { 1.0f, 1.0f, 0.0f };

		/*std::vector<T> data = {
			{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		};*/

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), data);
	}

	IndexBuffer* CreateIndexBuffer() override
	{
		std::vector<unsigned short> indices = {
			0, 1, 2,
			1, 3, 2
		};
		return new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	}



	VertexBuffer<T>* Temp(const std::vector<DirectX::XMFLOAT3>& colorList)
	{
		std::vector<T> data(4);
		data[0].pos = { -0.5f,  0.5f, 0.0f };
		data[1].pos = { 0.5f,  0.5f, 0.0f };
		data[2].pos = { -0.5f, -0.5f, 0.0f };
		data[3].pos = { 0.5f, -0.5f, 0.0f };
		data[0].vColor = colorList[0];
		data[1].vColor = colorList[1];
		data[2].vColor = colorList[2];
		data[3].vColor = colorList[3];

		/*std::vector<T> data = {
			{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
			{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
		};*/

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), data);
	}
};