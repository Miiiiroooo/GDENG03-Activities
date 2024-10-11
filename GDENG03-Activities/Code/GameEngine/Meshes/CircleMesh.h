#pragma once
#include "AMesh.h"
#include <SimpleMath.h>


using namespace DirectX::SimpleMath;

template <typename T>
class CircleMesh : public AMesh<T>
{
public:
	VertexBuffer<T>* CreateVertexBuffer() override
	{
		float size = 21;

		std::vector<T> data(size);
		data[0].pos = Vector3::Zero;
		data[0].vColor = { 1.0f, 1.0f, 1.0f };

		Vector2 dir = Vector2::UnitY;
		float currAngle = 0;
		float angleIncrements = 360.f / (size - 1.f);

		for (int i = 1; i < size; i++)
		{
			dir.x = sin(currAngle * M_PI / 180.f) / 2.f;
			dir.y = cos(currAngle * M_PI / 180.f) / 2.f;
			Vector3 newVert = Vector3(dir.x, dir.y, 0.0f); 

			data[i].pos = newVert; 
			data[i].vColor = { 1.0f, 1.0f, 1.0f };

			currAngle += angleIncrements;
		}

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), data);
	}

	IndexBuffer* CreateIndexBuffer() override
	{
		float size = 21;

		std::vector<unsigned short> indices;

		for (int i = 0; i < size - 1; i++)
		{
			std::vector<unsigned short> triangle;
			triangle.push_back(0);
			triangle.push_back(i + 1);
			triangle.push_back((i == size - 2) ? 1 : i + 2);

			indices.insert(indices.end(), triangle.begin(), triangle.end());
		}

		return new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	}


	VertexBuffer<T>* Temp(Vector3 color) 
	{
		float size = 21;

		std::vector<T> data(size);
		data[0].pos = Vector3::Zero;
		data[0].vColor = color;

		Vector2 dir = Vector2::UnitY;
		float currAngle = 0;
		float angleIncrements = 360.f / (size - 1.f);

		for (int i = 1; i < size; i++)
		{
			dir.x = sin(currAngle * M_PI / 180.f) / 2.f;
			dir.y = cos(currAngle * M_PI / 180.f) / 2.f;
			Vector3 newVert = Vector3(dir.x, dir.y, 0.0f);

			data[i].pos = newVert;
			data[i].vColor = color;

			currAngle += angleIncrements;
		}

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), data);
	}
};

