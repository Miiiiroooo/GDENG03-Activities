#include "AppWindow.h"

//#include <d3d11.h>
//#include <DirectXMath.h>




int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AppWindow app;

	if (app.Init())
	{
		while (app.IsRunning())
		{
			app.Broadcast();
		}
	}



	/*WNDCLASSEX wClass = {};
	wClass.cbSize = sizeof(wClass);
	wClass.style = CS_OWNDC;
	wClass.lpfnWndProc = DefWindowProc;
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.hInstance = hInstance;
	wClass.hCursor = nullptr;
	wClass.hIcon = nullptr;
	wClass.hIconSm = nullptr;
	wClass.hbrBackground = nullptr;
	wClass.lpszMenuName = nullptr;
	wClass.lpszClassName = "Temp";

	RegisterClassEx(&wClass);
	HWND hWnd = CreateWindowEx(0, "Temp", "Temp Window", WS_CAPTION | WS_MINIMIZEBOX, 300, 300, 640, 480, nullptr, nullptr, hInstance, nullptr);

	MSG msg = {  };
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}*/

	return 0;
}