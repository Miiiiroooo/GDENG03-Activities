#pragma once
#include "GameEngine/Meshes/EPrimitiveMeshTypes.h"
#include "GameEngine/Components/Physics/Rigidbody3D.h"
#include <reactphysics3d/reactphysics3d.h>


class PhysicsEngine
{
public:
	static PhysicsEngine* GetInstance();
	PhysicsEngine(const PhysicsEngine&) = delete;
	PhysicsEngine& operator=(const PhysicsEngine&) = delete;

	bool Init();
	bool Release();
	void Update(float dt);

	void RegisterRigidBody(RigidBody3D* rb);
	void UnregisterRigidBody(RigidBody3D* rb);

	rp3d::PhysicsCommon* GetPhysicsCommon();
	rp3d::CollisionShape* GetCollisionShape(EPrimitiveMeshTypes meshType);

private:
	PhysicsEngine() {};
	~PhysicsEngine() {};


private:
	static PhysicsEngine* sharedInstance;

	rp3d::PhysicsCommon* physicsCommon;
	rp3d::PhysicsWorld* physicsWorld;

	std::vector<RigidBody3D*> rigidBodyList;
	std::unordered_map<EPrimitiveMeshTypes, rp3d::CollisionShape*> collisionShapesTable;
};