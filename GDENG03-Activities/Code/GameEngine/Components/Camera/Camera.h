#pragma once
#include <SimpleMath.h>
#include "../AComponent.h"
#include "EProjectionTypes.h"
#include "../../../DirectXClasses/Buffers/BufferDataTypes.h"
#include "../../../DirectXClasses/SwapChain.h"


using namespace DirectX::SimpleMath;

class Camera : public AComponent
{
public:
	Camera(int width, int height);
	Camera(std::string name, int width, int height);
	~Camera();

	void Perform() override;
	VPMatrix CreateViewProjectionMatrix();

	Vector2 GetClippingPlane();
	void SetClippingPlane(float nearZ, float farZ);
	__declspec(property(get = GetClippingPlane, put = SetClippingPlane)) Vector2 ClippingPlane;


public:
	EProjectionTypes ProjectionType;
	Vector2 AspectRatio;
	float FieldOfView;

private:
	Vector2 clippingPlane;

	//SwapChain* swapChain;
	//Color bgColor;
};