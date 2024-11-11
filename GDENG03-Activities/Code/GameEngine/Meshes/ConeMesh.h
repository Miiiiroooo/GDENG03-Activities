#pragma once
#include "AMesh.h"
#include "../MathUtils.h"

template <typename T>
class ConeMesh : public AMesh<T>
{
public:
	int numPointsOnCircle = 20;

	VertexBuffer<T>* CreateVertexBuffer(bool isRainbowed) override
	{
		std::vector<T> vertices(numPointsOnCircle + 2);
		vertices[0].pos = Vector3(0.0f, -0.5f, 0.0f); 
		vertices[0].vColor = (isRainbowed) ?
			Vector3(MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange()) :
			this->color;


		float currAngle = 0;
		float angleIncrements = 360.f / (float)(numPointsOnCircle);

		for (int i = 1; i <= numPointsOnCircle; i++)
		{
			float x = sin(currAngle * M_PI / 180.f) / 2.f;
			float z = cos(currAngle * M_PI / 180.f) / 2.f;
			Vector3 newVert = Vector3(x, -0.5f, z); 

			vertices[i].pos = newVert;
			vertices[i].vColor = (isRainbowed) ?
				Vector3(MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange()) :
				this->color;

			currAngle += angleIncrements;
		}

		vertices[numPointsOnCircle + 1].pos = { 0.0f, 0.5f, 0.0f }; 
		vertices[numPointsOnCircle + 1].vColor = (isRainbowed) ? 
			Vector3(MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange()) :
			this->color;

		return new VertexBuffer<T>(GraphicsEngine::GetInstance(), vertices);
	}

	IndexBuffer* CreateIndexBuffer() override
	{
		std::vector<unsigned short> indices; 

		for (int i = 0; i < numPointsOnCircle; i++)
		{
			// insert circle triangle
			indices.push_back((i == numPointsOnCircle - 1) ? 1 : i + 2); 
			indices.push_back(i + 1); 
			indices.push_back(0); 
			// insert side triangle
			indices.push_back(numPointsOnCircle + 1); 
			indices.push_back(i + 1); 
			indices.push_back((i == numPointsOnCircle - 1) ? 1 : i + 2);
		}

		return new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	}
};