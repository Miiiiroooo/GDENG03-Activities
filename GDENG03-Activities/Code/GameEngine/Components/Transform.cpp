#include "Transform.h"
#include "../GameObjects/AGameObject.h"


Transform::Transform() : AComponent("Transform", EComponentTypes::Transform)
{
	globalPos = Vector3::Zero; 
	localPos = Vector3::Zero; 

	globalScale = Vector3::One;  
	localScale = Vector3::One;

	eulerAngles = Vector3::Zero; 
	localEulerAngles = Vector3::Zero;
	orientation = Quaternion::Identity;

	localRight = Vector3::Right;
	localUp = Vector3::Up;
	localForward = Vector3::Backward; // backward returns (0,0,1)
}

Transform::~Transform()
{

}

void Transform::Clone(AComponent* copy)
{
	Transform* copyTransform = (Transform*)copy;
	if (copyTransform == nullptr) return;

	// revisit this next time
	globalPos = copyTransform->globalPos;
	globalScale = copyTransform->globalScale;
	eulerAngles = copyTransform->eulerAngles;
}

void Transform::Perform()
{

}

TMatrix Transform::CreateTransformationMatrix()
{
	return TMatrix{
			Matrix::CreateScale(globalScale) * 
			Matrix::CreateFromQuaternion(orientation) * 
			Matrix::CreateTranslation(globalPos)
		};
}

void Transform::RecalculateChildTransformWithoutParent() 
{
	localPos = globalPos;
	localScale = globalScale;
	localEulerAngles = eulerAngles;

	// no need to update children since the local and global values are still the same 
}

void Transform::RecalculateChildTransformWithParent(const Transform* parent)
{
	this->SetLocalPosition(this->globalPos - parent->globalPos);

	// Vector3 division from SimpleMath defaults to 'inf' value if there's division by 0
	Vector3 newScale;
	newScale.x = (parent->globalScale.x == 0) ? 0 : (this->globalScale.x / parent->globalScale.x);
	newScale.y = (parent->globalScale.y == 0) ? 0 : (this->globalScale.y / parent->globalScale.y);
	newScale.z = (parent->globalScale.z == 0) ? 0 : (this->globalScale.z / parent->globalScale.z);
	this->SetLocalScale(newScale);

	UpdateLocalEulerAnglesWithChildren(parent);
}


#pragma region Position
Vector3 Transform::GetPosition()
{
	return globalPos;
}

void Transform::SetPosition(const Vector3& newPos)
{
	// set value
	globalPos = newPos;

	// update local position, taking consideration of the parent
	AGameObject* parentObj = owner->GetParent();

	localPos = (parentObj) ? 
		globalPos - parentObj->GetTransform()->globalPos : 
		globalPos; 

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform);
	for (int i = 0; i < transformsFromChildren.size(); i++)
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i];
		childTransform->SetPosition(newPos + childTransform->localPos);
	}
}

Vector3 Transform::GetLocalPosition()
{
	return localPos;
}

void Transform::SetLocalPosition(const Vector3& newPos)
{
	// set value
	localPos = newPos;

	// update global position, taking consideration of the parent
	AGameObject* parentObj = owner->GetParent(); 
	globalPos = (parentObj) ?
		localPos + parentObj->GetTransform()->globalPos :
		localPos;

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform); 
	for (int i = 0; i < transformsFromChildren.size(); i++) 
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i]; 
		childTransform->SetPosition(globalPos + childTransform->localPos); 
	}
}
#pragma endregion


#pragma region Scale
Vector3 Transform::GetLocalScale()
{
	return localScale;
}

void Transform::SetLocalScale(const Vector3& newScale)
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
	globalScale = (parentObj) ?
		localScale * parentObj->GetTransform()->globalScale :
		localScale;

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform);
	for (int i = 0; i < transformsFromChildren.size(); i++)
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i];
		childTransform->UpdateGlobalScaleWithChildren();
	}
}
#pragma endregion 


#pragma region Rotation
Vector3 Transform::GetEulerAngles()
{
	return eulerAngles;
}

Vector3 Transform::GetLocalEulerAngles()
{
	return localEulerAngles;
}

Vector3 Transform::GetLocalRight() 
{
	return localRight;
}

Vector3 Transform::GetLocalUp() 
{
	return localUp;
}

Vector3 Transform::GetLocalForward() 
{
	return localForward;
}


void Transform::Rotate(float xAngleInDeg, float yAngleInDeg, float zAngleInDeg)
{
	Rotate(Vector3(xAngleInDeg, yAngleInDeg, zAngleInDeg));
}

void Transform::Rotate(const Vector3& eulerInDeg)
{
	Quaternion yaw = Quaternion::CreateFromAxisAngle(localUp, eulerInDeg.y * (M_PI / 180.f));
	Quaternion pitch = Quaternion::CreateFromAxisAngle(localRight, eulerInDeg.x * (M_PI / 180.f));
	Quaternion roll = Quaternion::CreateFromAxisAngle(localForward, eulerInDeg.z * (M_PI / 180.f));
	Quaternion toRotate = yaw * pitch * roll;
	//Quaternion toRotate = Quaternion::CreateFromYawPitchRoll(eulerInDeg * (M_PI / 180.f)); 
	orientation *= toRotate;

	// update euler angles and local vectors
	eulerAngles += eulerInDeg;
	UpdateLocalVectors(); 

	// update local euler angles, taking consideration of the parent
	AGameObject* parentObj = owner->GetParent();

	localEulerAngles = (parentObj) ?
		eulerAngles - parentObj->GetTransform()->eulerAngles :
		eulerAngles;

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform);
	for (int i = 0; i < transformsFromChildren.size(); i++)
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i];
		childTransform->RotateFromParent(eulerInDeg, toRotate, this);
	}
}

void Transform::RotateFromParent(const Vector3& eulerInDeg, const Quaternion& toRotate, const Transform* parent)
{
	orientation *= toRotate;  
	 
	// update all euler angles and local vectors
	eulerAngles += eulerInDeg;
	localEulerAngles = eulerAngles - parent->eulerAngles;
	UpdateLocalVectors(); 

	// update position based on an offset from parent
	Vector3 displacement = globalPos - parent->globalPos;
	displacement = Vector3::Transform(displacement, toRotate);
	SetPosition(parent->globalPos + displacement);

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform); 
	for (int i = 0; i < transformsFromChildren.size(); i++) 
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i]; 
		childTransform->RotateFromParent(eulerInDeg, toRotate, this);
	}
}


void Transform::Rotate(const Vector3& axis, float angleInDeg)
{
	Quaternion toRotate = Quaternion::CreateFromAxisAngle(axis, DirectX::XMConvertToRadians(angleInDeg)); 
	orientation *= toRotate;

	// update euler angles and local vectors
	eulerAngles += toRotate.ToEuler() * (180.f / M_PI);
	UpdateLocalVectors();

	// update local euler angles, taking consideration of the parent
	AGameObject* parentObj = owner->GetParent(); 

	localEulerAngles = (parentObj) ? 
		eulerAngles - parentObj->GetTransform()->eulerAngles : 
		eulerAngles;

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform); 
	for (int i = 0; i < transformsFromChildren.size(); i++) 
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i]; 
		childTransform->RotateFromParent(toRotate, this);
	}
}

void Transform::RotateFromParent(const Quaternion& toRotate, const Transform* parent)
{
	orientation *= toRotate;

	// update all euler angles and local vectors
	eulerAngles += toRotate.ToEuler() * (180.f / M_PI);
	localEulerAngles = eulerAngles - parent->eulerAngles;
	UpdateLocalVectors();

	// update position based on an offset from parent
	Vector3 displacement = globalPos - parent->globalPos; 
	displacement = Vector3::Transform(displacement, toRotate);
	SetPosition(parent->globalPos + displacement); 

	// update all the transforms of every 'descendant'
	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform);
	for (int i = 0; i < transformsFromChildren.size(); i++)
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i];
		childTransform->RotateFromParent(toRotate, this);
	}
}


void Transform::UpdateLocalEulerAnglesWithChildren(const Transform* parent)
{
	localEulerAngles = eulerAngles - parent->eulerAngles;

	auto transformsFromChildren = owner->GetComponentsInChildrenOfType(EComponentTypes::Transform); 
	for (int i = 0; i < transformsFromChildren.size(); i++) 
	{
		Transform* childTransform = (Transform*)transformsFromChildren[i]; 
		childTransform->UpdateLocalEulerAnglesWithChildren(this);
	}
}

void Transform::UpdateLocalVectors()
{
	Vector3::Transform(Vector3::Right, orientation, localRight);
	Vector3::Transform(Vector3::Up, orientation, localUp);
	Vector3::Transform(Vector3::Backward, orientation, localForward); // backward returns (0,0,1)
}
#pragma endregion