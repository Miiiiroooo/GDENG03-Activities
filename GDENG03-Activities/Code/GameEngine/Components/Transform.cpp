#include "Transform.h"
#include "../GameObjects/AGameObject.h"


Transform::Transform() : AComponent("Transform", EComponentTypes::Transform)
{
	globalPos = { 0.0f, 0.0f, 0.0f };
	localPos = { 0.0f, 0.0f, 0.0f };

	globalScale = { 1.0f, 1.0f, 1.0f };
	localScale = { 1.0f, 1.0f, 1.0f };

	eulerAngles = { 0.0f, 0.0f, 0.0f };
	localRight = { 1.0f, 0.0f, 0.0f };
	localUp = { 0.0f, 1.0f, 0.0f };
	localForward = { 0.0f, 0.0f, 1.0f };
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
			//DirectX::XMMatrixRotationX(temp * M_PI / 180.f) * 
			DirectX::XMMatrixScaling(globalScale.x, globalScale.y, globalScale.z) *
			DirectX::XMMatrixTranslation(globalPos.x, globalPos.y, globalPos.z) *
			DirectX::XMMatrixPerspectiveLH(1, 0.75f, 0.5f, 10.f)
		)};
}

#pragma region Position
DirectX::XMFLOAT3 Transform::GetPosition()
{
	return globalPos;
}

void Transform::SetPosition(const DirectX::XMFLOAT3& newPos)
{
	// set value
	globalPos = newPos;

	// update local position, taking consideration of the parent
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

	// update all the transforms of every 'descendant'
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
	// set value
	localPos = newPos;

	// update global position, taking consideration of the parent
	AGameObject* parentObj = owner->GetParent(); 
	if (parentObj) 
	{
		globalPos.x = localPos.x + parentObj->GetTransform()->globalPos.x;
		globalPos.y = localPos.y + parentObj->GetTransform()->globalPos.y; 
		globalPos.z = localPos.z + parentObj->GetTransform()->globalPos.z; 
	}

	// update all the transforms of every 'descendant'
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
#pragma endregion

#pragma region Scale
DirectX::XMFLOAT3 Transform::GetLocalScale()
{
	return localScale;
}

void Transform::SetLocalScale(const DirectX::XMFLOAT3& newScale)
{
	// set value
	localScale = newScale; 

	// update global scale
	UpdateGlobalScaleWithChildren(); 
}

void Transform::UpdateGlobalScaleWithChildren()
{
	// update global scale, taking consideration of the parent
	AGameObject* parentObj = owner->GetParent();
	if (parentObj)
	{
		globalScale.x = localScale.x * parentObj->GetTransform()->globalScale.x;
		globalScale.y = localScale.y * parentObj->GetTransform()->globalScale.y;
		globalScale.z = localScale.z * parentObj->GetTransform()->globalScale.z;
	}
	else
	{
		globalScale = localScale;
	}

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform);
	for (int i = 0; i < transformsFromChildren.size(); i++)
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i];
		childTransform->UpdateGlobalScaleWithChildren();
	}
}
#pragma endregion 