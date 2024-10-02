#pragma once
#include <Windows.h>
#include <string>
#include "GraphicsEngine.h"

class Window
{
public: 
	Window();
	~Window();

	virtual bool Init(int width, int height, std::string windowName);
	virtual bool Release();
	bool Update();
	bool IsRunning();

	RECT GetClientWindowRect();


protected:
	virtual void OnCreate(HWND hWnd) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDestroy();

	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT CALLBACK HandleWindowMessages(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


protected:
	UINT width;
	UINT height;
	RECT windowSize;

	HWND hWnd;
	HWND parentHwnd;
	std::string windowClassName;
	DWORD windowStyles;

	bool isRunning;
};