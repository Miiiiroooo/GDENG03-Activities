#pragma once
#include <SimpleMath.h>
#include "AComponent.h"
#include "../../DirectXClasses/Buffers/BufferDataTypes.h"


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

	DirectX::XMFLOAT3 GetLocalScale();
	void SetLocalScale(const DirectX::XMFLOAT3& newScale);
	__declspec(property(get = GetLocalScale, put = SetLocalScale)) DirectX::XMFLOAT3 LocalScale;
	#pragma endregion



private:
	void UpdateGlobalScaleWithChildren();


private:
	DirectX::XMFLOAT3 globalPos;
	DirectX::XMFLOAT3 localPos;

	DirectX::XMFLOAT3 globalScale; 
	DirectX::XMFLOAT3 localScale; 

	DirectX::XMFLOAT3 eulerAngles;
	DirectX::XMFLOAT4 orientation;
	DirectX::XMFLOAT3 localRight;
	DirectX::XMFLOAT3 localUp;
	DirectX::XMFLOAT3 localForward;
};