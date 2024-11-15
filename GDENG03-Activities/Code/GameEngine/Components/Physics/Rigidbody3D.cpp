#include "Rigidbody3D.h"
#include "GameEngine/MathUtils.h"

RigidBody3D::RigidBody3D(EPrimitiveMeshTypes shapeType) : AComponent("RigidBody3D", EComponentTypes::Physics), shapeType(shapeType)
{
	rb = nullptr;
	collider = nullptr;
	shapeTransform = rp3d::Transform::identity();
}

RigidBody3D::~RigidBody3D()
{

}

void RigidBody3D::Clone(AComponent* copy)
{
	RigidBody3D* copyRB = (RigidBody3D*)copy;
	if (copyRB == nullptr) return;

	Mass = copyRB->Mass;
	BodyType = copyRB->BodyType;
	GravityEnabled = copyRB->GravityEnabled;
	LinearDamping = copyRB->LinearDamping;
	AngularDamping = copyRB->AngularDamping;
	LinearLocks = copyRB->LinearLocks;
	AngularLocks = copyRB->AngularLocks;
}

void RigidBody3D::Perform()
{

}

#pragma region Getters-Setters
bool RigidBody3D::Init(rp3d::RigidBody* rb)
{
	if (rb == nullptr) return false;

	this->rb = rb;

	// create collider


	return true;
}

rp3d::RigidBody* RigidBody3D::GetRigidBody()
{
	return rb;
}

float RigidBody3D::GetMass()
{
	return rb->getMass();
}

void RigidBody3D::SetMass(const float& newMass)
{
	rb->setMass(newMass);
}

rp3d::BodyType RigidBody3D::GetBodyType()
{
	return rb->getType();
}

void RigidBody3D::SetBodyType(const rp3d::BodyType& newType)
{
	rb->setType(newType);
}

bool RigidBody3D::IsGravityEnabled()
{
	return rb->isGravityEnabled();
}

void RigidBody3D::EnableGravity(const bool& status)
{
	rb->enableGravity(status);
}

float RigidBody3D::GetLinearDamping()
{
	return rb->getLinearDamping();
}

void RigidBody3D::SetLinearDamping(const float& newDamping)
{
	rb->setLinearDamping(newDamping);
}

float RigidBody3D::GetAngularDamping()
{
	return rb->getAngularDamping();
}

void RigidBody3D::SetAngularDamping(const float& newDamping)
{
	rb->setAngularDamping(newDamping);
}

Vector3 RigidBody3D::GetLinearLocks()
{
	return MathUtils::ConvertVector(rb->getLinearLockAxisFactor());
}

void RigidBody3D::SetLinearLocks(const Vector3& newLocks)
{
	rb->setLinearLockAxisFactor(MathUtils::ConvertVector(newLocks));
}

Vector3 RigidBody3D::GetAngularLocks()
{
	return MathUtils::ConvertVector(rb->getAngularLockAxisFactor());
}

void RigidBody3D::SetAngularLocks(const Vector3& newLocks)
{
	rb->setAngularLockAxisFactor(MathUtils::ConvertVector(newLocks));
}
#pragma endregion


void RigidBody3D::ApplyForce(const Vector3& force)
{
	rb->applyLocalForceAtCenterOfMass(MathUtils::ConvertVector(force));
}

void RigidBody3D::ApplyForce(const Vector3& force, const Vector3& point)
{
	rb->applyLocalForceAtLocalPosition(MathUtils::ConvertVector(force), MathUtils::ConvertVector(point));
}

void RigidBody3D::ApplyTorque(const Vector3& torque)
{
	rb->applyLocalTorque(MathUtils::ConvertVector(torque));
}