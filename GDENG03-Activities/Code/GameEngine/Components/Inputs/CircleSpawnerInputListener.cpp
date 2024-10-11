#include "CircleSpawnerInputListener.h"


CircleSpawnerInputListener::CircleSpawnerInputListener(CircleSpawner* spawner) : GenericInputController("CircleInput"), spawner(spawner)
{

}

CircleSpawnerInputListener::~CircleSpawnerInputListener()
{

}

void CircleSpawnerInputListener::Perform()
{
	if (wParam == VK_SPACE && !(lParam & 0x40000000))
	{
		spawner->CreateCircle();
	}
	else if (wParam == VK_BACK && !(lParam & 0x40000000))
	{
		spawner->DeleteRecentCircle();
	}
	else if (wParam == VK_DELETE && !(lParam & 0x40000000))
	{
		spawner->DeleteAllCircles();
	}
}