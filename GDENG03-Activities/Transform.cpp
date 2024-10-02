#include "Transform.h"
#include "AGameObject.h"


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

	AGameObject* parentObj = owner->GetParent();
	if (parentObj)
	{
		localPos.x = globalPos.x - parentObj->GetTransform()->globalPos.x;
		localPos.y = globalPos.y - parentObj->GetTransform()->globalPos.y;
		localPos.z = globalPos.z - parentObj->GetTransform()->globalPos.z;
	}
	else
	{
		localPos = newPos;
	}

	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform);
	for (int i = 0; i < transformsFromChildren.size(); i++)
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i];
		DirectX::XMFLOAT3 newChildPos = newPos;
		newChildPos.x += childTransform->localPos.x;
		newChildPos.y += childTransform->localPos.y;
		newChildPos.z += childTransform->localPos.z;
		childTransform->SetPosition(newChildPos);
	}
}

DirectX::XMFLOAT3 Transform::GetLocalPosition()
{
	return localPos;
}

void Transform::SetLocalPosition(const DirectX::XMFLOAT3& newPos)
{
	localPos = newPos;

	AGameObject* parentObj = owner->GetParent(); 
	if (parentObj) 
	{
		globalPos.x = localPos.x + parentObj->GetTransform()->globalPos.x;
		globalPos.y = localPos.y + parentObj->GetTransform()->globalPos.y; 
		globalPos.z = localPos.z + parentObj->GetTransform()->globalPos.z; 
	}

	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform); 
	for (int i = 0; i < transformsFromChildren.size(); i++) 
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i]; 
		DirectX::XMFLOAT3 newChildPos = globalPos; 
		newChildPos.x += childTransform->localPos.x; 
		newChildPos.y += childTransform->localPos.y; 
		newChildPos.z += childTransform->localPos.z; 
		childTransform->SetPosition(newChildPos); 
	}
}