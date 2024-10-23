#pragma once
#include "AMesh.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

template <typename T>
class CylinderMesh : public AMesh<T>
{
public:
	float numPointsOnCircle = 20;

	VertexBuffer<T>* CreateVertexBuffer() override
	{
		int total = numPointsOnCircle * 2 + 2; 
		std::vector<T> data(total); 
		data[0].pos = { 0.0f, -1.0f, 0.0f };
		data[0].vColor = { 1.0f, 1.0f, 1.0f };
		data[total / 2].pos = { 0.0f, 1.0f, 0.0f };
		data[total / 2].vColor = { 1.0f, 1.0f, 1.0f };

		Vector2 dir = Vector2::UnitY;
		float currAngle = 0;
		float angleIncrements = 360.f / (numPointsOnCircle);

		for (int i = 1; i <= numPointsOnCircle; i++)
		{
			dir.x = sin(currAngle * M_PI / 180.f) / 2.f;
			dir.y = cos(currAngle * M_PI / 180.f) / 2.f;

			data[i].pos = { dir.x, -1.0f, dir.y };
			data[i].vColor = { 1.0f, 1.0f, 1.0f };  
			data[i + total / 2].pos = { dir.x, 1.0f, dir.y };
			data[i + total / 2].vColor = { 1.0f, 1.0f, 1.0f };  

			currAngle += angleIncrements;
		}

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), data);
	}

	IndexBuffer* CreateIndexBuffer() override
	{
		std::vector<unsigned short> indices;

		int halfSize = numPointsOnCircle + 1;

		for (int i = 0; i < numPointsOnCircle; i++)
		{
			std::vector<unsigned short> triangles;
			int bottomA = i + 1;
			int bottomB = (i == numPointsOnCircle - 1) ? 1 : i + 2;
			int topA = halfSize + i + 1;
			int topB = (i == numPointsOnCircle - 1) ? halfSize + 1 : halfSize + i + 2; 

			// insert bottom circle triangle
			triangles.push_back(bottomB);  
			triangles.push_back(bottomA);  
			triangles.push_back(0);
			// insert top circle triangle
			triangles.push_back(halfSize);
			triangles.push_back(topA); 
			triangles.push_back(topB); 
			// insert side triangle A
			triangles.push_back(bottomB); 
			triangles.push_back(topA);  
			triangles.push_back(bottomA);  
			// insert side triangle B
			triangles.push_back(topA); 
			triangles.push_back(bottomB);  
			triangles.push_back(topB);  

			indices.insert(indices.end(), triangles.begin(), triangles.end());
		}

		return new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	}
};
