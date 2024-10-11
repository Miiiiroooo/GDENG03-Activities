#include "CircleObject.h"
#include "../../Components/Renderer/MeshRenderer.h"
#include "../../Managers/GameObjectManager.h"
#include "../../Components/Scripts/CircleBehavior.h"


CircleObject::CircleObject(float aspectRatio) : AGameObject("CircleObject"), aspectRatio(aspectRatio)
{
	randScale = (float)rand() / (float)RAND_MAX; // rand btween 0 - 1
	randScale *= (0.4f - 0.05f); // rand between range of 0.0 - 0.35
	randScale += 0.05f; // rand between range of 0.05 - 0.4
}

CircleObject::~CircleObject()
{

}

void CircleObject::Initialize()
{
	float randX = (float)rand() / (float)RAND_MAX - 0.5f; 
	float randY = (float)rand() / (float)RAND_MAX - 0.5f; 
	transform->Position = Vector3(randX, randY, 1); 

	transform->LocalScale = Vector3(randScale, aspectRatio * randScale, 1); 

	Vector3 color((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);

	MeshRenderer* r = new MeshRenderer(L"DefaultShader");
	r->CreateCircle(color);
	AttachComponent(r); 
	GameObjectManager::GetInstance()->BindRendererToShader(r);

	CircleBehavior* behavior = new CircleBehavior();
	AttachComponent(behavior);
}