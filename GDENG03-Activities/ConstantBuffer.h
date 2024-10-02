#pragma once
#include <wrl.h>
#include "AD3D11Object.h"


template<typename T>
class ConstantBuffer : public AD3D11Object
{
public:
	ConstantBuffer(GraphicsEngine* gfx);
	~ConstantBuffer();

	bool Init() override;
	bool Release() override;
	bool SetConstants(const T& constants);


protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};


template<typename T>
class VertexConstantBuffer : public ConstantBuffer<T>
{
private:
	using AD3D11Object::gfx;
	using ConstantBuffer<T>::pConstantBuffer;

public:
	VertexConstantBuffer(GraphicsEngine* gfx) : ConstantBuffer<T>(gfx) {} 
	~VertexConstantBuffer() {}
	void BindToPipeline() override;
};


template<typename T>
class GeometryConstantBuffer : public ConstantBuffer<T>
{
private:
	using AD3D11Object::gfx;
	using ConstantBuffer<T>::pConstantBuffer;

public:
	GeometryConstantBuffer(GraphicsEngine* gfx) : ConstantBuffer<T>(gfx) {}
	~GeometryConstantBuffer() {}
	void BindToPipeline() override;
};


template<typename T>
class PixelConstantBuffer : public ConstantBuffer<T>
{
private:
	using AD3D11Object::gfx;
	using ConstantBuffer<T>::pConstantBuffer;

public:
	PixelConstantBuffer(GraphicsEngine* gfx) : ConstantBuffer<T>(gfx) {}
	~PixelConstantBuffer() {}
	void BindToPipeline() override;
};