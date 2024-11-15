#include "PhysicsEngine.h"
#include "../MathUtils.h"
#include "GameEngine/Components/Transform.h"


#pragma region Singleton
PhysicsEngine* PhysicsEngine::sharedInstance = NULL;

PhysicsEngine* PhysicsEngine::GetInstance()
{
	if (sharedInstance == NULL)
	{
		sharedInstance = new PhysicsEngine();
	}

	return sharedInstance;
}
#pragma endregion


bool PhysicsEngine::Init()
{
	physicsCommon = new rp3d::PhysicsCommon();

	rp3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 30; 
	settings.defaultPositionSolverNbIterations = 15;
	settings.gravity = rp3d::Vector3(0, -9.81, 0);  

	physicsWorld = physicsCommon->createPhysicsWorld(settings);
	//physicsWorld->setTimeBeforeSleep(2.0f);

	return true;
}

bool PhysicsEngine::Release()
{
	for (int i = (int)rigidBodyList.size() - 1; i >= 0; i--)
	{
		UnregisterRigidBody(rigidBodyList[i]);
	}

	for (auto& shapePair : collisionShapesTable)
	{
		// destory shapes
	}

	physicsCommon->destroyPhysicsWorld(physicsWorld);
	delete physicsCommon;

	return true;
}

void PhysicsEngine::Update(float dt)
{
	physicsWorld->update(dt);

	for (auto& rb : rigidBodyList)
	{
		rb->Perform();
	}
}


void PhysicsEngine::RegisterRigidBody(RigidBody3D* rb)
{
	auto itr = std::find(rigidBodyList.begin(), rigidBodyList.end(), rb);
	if (itr != rigidBodyList.end()) return;

	rp3d::Vector3 position = MathUtils::ConvertVector(rb->GetTransform()->Position);
	rp3d::Quaternion orientation = MathUtils::ConvertQuaternion(rb->GetTransform()->GetOrientation());
	rp3d::Transform rTransform = rp3d::Transform(position, orientation);

	if (rb->Init(physicsWorld->createRigidBody(rTransform)))
	{
		rigidBodyList.push_back(rb);
	}
}

void PhysicsEngine::UnregisterRigidBody(RigidBody3D* rb)
{
	auto itr = std::find(rigidBodyList.begin(), rigidBodyList.end(), rb);
	if (itr == rigidBodyList.end())  return;
	
	physicsWorld->destroyRigidBody(rb->GetRigidBody());

	rigidBodyList.erase(itr); 
	rigidBodyList.shrink_to_fit(); 
}


rp3d::PhysicsCommon* PhysicsEngine::GetPhysicsCommon()
{
	return physicsCommon;
}

rp3d::CollisionShape* PhysicsEngine::GetCollisionShape(EPrimitiveMeshTypes meshType)
{
	if (collisionShapesTable[meshType] == nullptr)
	{
		switch (meshType)
		{
		case EPrimitiveMeshTypes::Cube:
			collisionShapesTable[meshType] = physicsCommon->createBoxShape(rp3d::Vector3(1.0f, 1.0f, 1.0f)); break;
		case EPrimitiveMeshTypes::Sphere:
			collisionShapesTable[meshType] = physicsCommon->createSphereShape(1.0f); break;
		case EPrimitiveMeshTypes::Plane: 

		case EPrimitiveMeshTypes::Cylinder: 

		case EPrimitiveMeshTypes::Cone: 

		default:
			return nullptr;
		}
	}

	return nullptr;
}
