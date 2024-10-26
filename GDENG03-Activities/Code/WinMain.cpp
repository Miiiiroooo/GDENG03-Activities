#include "GameEngine/GameEngineWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameEngineWindow gameEngine(60);  

	if (gameEngine.Init(1280, 960, "Aamir Akim"))  
	{
		while (gameEngine.IsRunning())  
		{
			gameEngine.Update();  
		}
	}

	gameEngine.Release();  

	return 0;
}