#pragma once

struct Vector3
{
	float x, y, z;

	Vector3() : x(0), y(0), z(0)
	{
	}

	Vector3(float x, float y, float z) : x(x), y(y), z(z)
	{
	}

	Vector3(const Vector3& copy) : x(copy.x), y(copy.y), z(copy.z)
	{
	}
};


struct Vector4
{
	float x, y, z, w;

	Vector4() : x(0), y(0), z(0), w(0)
	{
	}

	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{
	}

	Vector4(const Vector4& copy) : x(copy.x), y(copy.y), z(copy.z), w(copy.w)
	{
	}
};


struct VertexData
{
	Vector3 pos;
	Vector3 vColor;
	Vector3 pp;
	Vector3 cc;


	VertexData()
	{
	}

	VertexData(const Vector3& pos, const Vector3& pp, const Vector3& vColor, const Vector3& vColor1) : pos(pos), pp(pp), vColor(vColor), cc(cc)
	{
	}

	VertexData(const VertexData& copy) : pos(copy.pos), pp(copy.pp), vColor(copy.vColor), cc(copy.cc)
	{
	}
};


__declspec(align(16))
struct ConstantData
{
	float m_angle;
};
