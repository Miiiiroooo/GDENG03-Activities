#include "GameEngine/GameEngineWindow.h"
#include <time.h>
#include <reactphysics3d/reactphysics3d.h>



int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL)); 

    // First you need to create the PhysicsCommon object.
    // This is a factory module that you can use to create physics
    // world and other objects. It is also responsible for
    // logging and memory management
    rp3d::PhysicsCommon physicsCommon;

    // Create a physics world
    rp3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld();

    // Create a rigid body in the world
    rp3d::Vector3 position(0, 20, 0);
    rp3d::Quaternion orientation = rp3d::Quaternion::identity();
    rp3d::Transform transform(position, orientation);
    rp3d::RigidBody* body = world->createRigidBody(transform);

    const float timeStep = 1.0f / 60.0f;

    // Step the simulation a few steps
    for (int i = 0; i < 20; i++) {

        world->update(timeStep);

        // Get the updated position of the body
        const rp3d::Transform& transform = body->getTransform();
        const rp3d::Vector3& position = transform.getPosition();

        // Display the position of the body
        OutputDebugString(("Body Position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + 
            std::to_string(position.z) + ")\n").c_str());
    }



	/*GameEngineWindow gameEngine(60);  

	if (gameEngine.Init(960, 720, "Aamir Akim")) 
	{
		while (gameEngine.IsRunning())  
		{
			gameEngine.Update();  
		}
	}

	gameEngine.Release(); */ 

	return 0;
}