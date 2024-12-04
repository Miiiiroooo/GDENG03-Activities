#pragma once
#include "AMesh.h"
#include "../MathUtils.h"
#include <SimpleMath.h>

using namespace DirectX::SimpleMath;

class CapsuleMesh : public AMesh
{
public:
	float radius = 0.5f;
	int longitudinalSize = 10;
	int latitudinalSize = 12;

	std::vector<Vector3> GetVertexPositions() override
	{
		int total = (longitudinalSize % 2 == 0 ? longitudinalSize : longitudinalSize - 1) * latitudinalSize + 2;
		int indexReduc = 0;
		std::vector<Vector3> vertices(total);

		// create top hemisphere
		CreateHemisphere(true, indexReduc, vertices); 

		// create bottom hemisphere
		CreateHemisphere(false, indexReduc, vertices); 

		return vertices;
	}

	void CreateHemisphere(bool isTop, int& indexReduc, std::vector<Vector3>& vertices)
	{
		float itr1Start = isTop ? 0.0f : std::ceil(longitudinalSize / 2.f); 
		float itr1End = isTop ? std::floor(longitudinalSize / 2.f) : longitudinalSize; 
		float minLongiAngle = isTop ? 0.0f : M_PI_2;
		float maxLongiAngle = isTop ? M_PI_2 : M_PI;
		float yOffset = isTop ? 0.5f : -0.5f;

		for (int i = itr1Start; i <= itr1End; i++)
		{
			float lon = MathUtils::Map((float)i, itr1Start, itr1End, minLongiAngle, maxLongiAngle);
			float y = radius * cos(lon) + yOffset;

			for (int j = 0; j < latitudinalSize; j++)
			{
				if (MathUtils::ApproximatelyEqualTo(std::fmod(lon, M_PI), 0.f) && j > 0)
				{
					indexReduc += latitudinalSize - 1;
					break;
				}

				float lat = MathUtils::Map((float)j, 0.0f, (float)latitudinalSize, (float)0, (float)2 * M_PI);
				float x = radius * sin(lon) * cos(lat);
				float z = radius * sin(lon) * sin(lat);

				int index = (!isTop && longitudinalSize % 2 == 0 ? i + 1 : i) * latitudinalSize + j - indexReduc;
				vertices[index] = { x, y, z };
			}
		}
	}

	std::vector<unsigned short> GetIndices() override
	{
		std::vector<unsigned short> indices;

		int itr1End = longitudinalSize % 2 == 0 ? longitudinalSize + 1 : longitudinalSize;

		for (int i = 0; i < itr1End; i++)
		{
			int bottomStart = i * latitudinalSize + 1; 
			int topStart = (i - 1) * latitudinalSize + 1; 

			for (int j = 0; j < latitudinalSize; j++) 
			{
				int topA = topStart + j;
				int topB = (j == latitudinalSize - 1) ? topStart : topStart + j + 1;
				int bottomA = bottomStart + j; 
				int bottomB = (j == latitudinalSize - 1) ? bottomStart : bottomStart + j + 1; 

				if (i == 0)
				{
					indices.push_back(0);
					indices.push_back(bottomB);
					indices.push_back(bottomA);
				}
				else if (i == itr1End - 1)
				{
					indices.push_back(bottomStart); 
					indices.push_back(topA); 
					indices.push_back(topB); 
				}
				else
				{
					indices.push_back(topA);
					indices.push_back(topB);
					indices.push_back(bottomA);

					indices.push_back(topB);
					indices.push_back(bottomB);
					indices.push_back(bottomA);
				}
			}
		}

		return indices;
	}
};