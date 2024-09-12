#pragma once
#include <Windows.h>

class Window
{
public: 
	Window();
	~Window();

	bool Init();
	bool Broadcast();
	bool Release();
	bool IsRunning();

	RECT GetClientWindowRect();
	void SetHWND(HWND newHWND);

	virtual void OnCreate() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDestroy();


protected:
	HWND hWnd;
	bool isRunning;
};