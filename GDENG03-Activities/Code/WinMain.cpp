#include "GameEngine/GameEngineWindow.h"
#include "GameEngine/Components/Transform.h"
#include "GameEngine/GameObjects/EmptyGameObject.h"
#include <time.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));

	GameEngineWindow gameEngine(60);  

	if (gameEngine.Init(640, 480, "Aamir Akim"))  
	{
		while (gameEngine.IsRunning())  
		{
			gameEngine.Update();  
		}
	}

	gameEngine.Release();  

	return 0;
}