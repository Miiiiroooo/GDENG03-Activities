#pragma once
#include <reactphysics3d/reactphysics3d.h>


class PhysicsEngine
{
public:
	static PhysicsEngine* GetInstance();
	PhysicsEngine(const PhysicsEngine&) = delete;
	PhysicsEngine& operator=(const PhysicsEngine&) = delete;

	bool Init();
	bool Release();

private:
	PhysicsEngine() {};
	~PhysicsEngine() {};


private:
	static PhysicsEngine* sharedInstance;

	rp3d::PhysicsCommon* physicsCommon;
	rp3d::PhysicsWorld* physicsWorld;
};