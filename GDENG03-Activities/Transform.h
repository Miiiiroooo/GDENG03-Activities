#pragma once
#include <DirectXMath.h>
#include "AComponent.h"
#include "BufferDataTypes.h"


class Transform : public AComponent
{
public:
	Transform();
	~Transform();

	void Perform() override;
	TMatrix CreateTransformationMatrix();

#pragma region Properties
	DirectX::XMFLOAT3 GetPosition();
	void SetPosition(const DirectX::XMFLOAT3& newPos);
	__declspec(property(get = GetPosition, put = SetPosition)) DirectX::XMFLOAT3 Position;

	DirectX::XMFLOAT3 GetLocalPosition();
	void SetLocalPosition(const DirectX::XMFLOAT3& newPos);
	__declspec(property(get = GetLocalPosition, put = SetLocalPosition)) DirectX::XMFLOAT3 LocalPosition;
#pragma endregion


public:
	DirectX::XMFLOAT3 Scale;


private:
	DirectX::XMFLOAT3 globalPos;
	DirectX::XMFLOAT3 localPos;

	DirectX::XMFLOAT3 localRight;
	DirectX::XMFLOAT3 localUp;
	DirectX::XMFLOAT3 localForward;

	DirectX::XMFLOAT3 eulerAngles;
	// add orientation/quaternion
};