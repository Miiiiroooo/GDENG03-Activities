#include "Transform.h"


Transform::Transform() : AComponent("Transform", EComponentTypes::Transform)
{
	globalPos = { 0.0f, 0.0f, 0.0f };
	localPos = { 0.0f, 0.0f, 0.0f };
	Scale = { 1.0f, 1.0f, 1.0f };
	localRight = { 1.0f, 0.0f, 0.0f };
	localUp = { 0.0f, 1.0f, 0.0f };
	localForward = { 0.0f, 0.0f, 1.0f };
	eulerAngles = { 0.0f, 0.0f, 0.0f };
}

Transform::~Transform()
{

}

void Transform::Perform()
{

}

TMatrix Transform::CreateTransformationMatrix()
{
	return TMatrix{
		DirectX::XMMatrixTranspose(
			// add rotation here   
			DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z) *
			DirectX::XMMatrixTranslation(globalPos.x, globalPos.y, globalPos.z)
		)};
}

DirectX::XMFLOAT3 Transform::GetPosition()
{
	return globalPos;
}

void Transform::SetPosition(const DirectX::XMFLOAT3& newPos)
{
	globalPos = newPos;
}

DirectX::XMFLOAT3 Transform::GetLocalPosition()
{
	return localPos;
}

void Transform::SetLocalPosition(const DirectX::XMFLOAT3& newPos)
{
	localPos = newPos;
}