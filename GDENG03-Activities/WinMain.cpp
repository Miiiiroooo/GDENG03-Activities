#include "GameEngineWindow.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameEngineWindow gameEngine;

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