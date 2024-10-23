#pragma once
#include "AMesh.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath; 

template <typename T>
class ConeMesh : public AMesh<T>
{
public:
	float numPointsOnCircle = 20;

	VertexBuffer<T>* CreateVertexBuffer() override
	{
		std::vector<T> data(numPointsOnCircle + 2);
		data[0].pos = Vector3::Zero;
		data[0].vColor = { 1.0f, 1.0f, 1.0f };

		Vector2 dir = Vector2::UnitY;
		float currAngle = 0;
		float angleIncrements = 360.f / (numPointsOnCircle);

		for (int i = 1; i <= numPointsOnCircle; i++)
		{
			dir.x = sin(currAngle * M_PI / 180.f) / 2.f;
			dir.y = cos(currAngle * M_PI / 180.f) / 2.f;
			Vector3 newVert = Vector3(dir.x, 0.0f, dir.y); 

			data[i].pos = newVert;
			data[i].vColor = { 1.0f, 1.0f, 1.0f };

			currAngle += angleIncrements;
		}

		data[numPointsOnCircle + 1].pos = { 0.0f, 2.0f, 0.0f }; 
		data[numPointsOnCircle + 1].vColor = { 1.0f, 1.0f, 1.0f }; 

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), data);
	}

	IndexBuffer* CreateIndexBuffer() override
	{
		std::vector<unsigned short> indices; 

		for (int i = 0; i < numPointsOnCircle; i++)
		{
			std::vector<unsigned short> triangles; 
			// insert circle triangle
			triangles.push_back((i == numPointsOnCircle - 1) ? 1 : i + 2); 
			triangles.push_back(i + 1);
			triangles.push_back(0); 
			// insert side triangle
			triangles.push_back(numPointsOnCircle + 1);
			triangles.push_back(i + 1);
			triangles.push_back((i == numPointsOnCircle - 1) ? 1 : i + 2); 

			indices.insert(indices.end(), triangles.begin(), triangles.end()); 
		}

		return new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	}
};