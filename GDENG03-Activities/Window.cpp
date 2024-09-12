#include "Window.h"
#include "WindowsMessageMap.h"
 

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//static WindowsMessageMap mm;
	//OutputDebugString(mm(msg, lParam, wParam).c_str());

	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
		window->SetHWND(hWnd);
		window->OnCreate();
		break;
	}

	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		window->OnDestroy();
		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam); 
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}



Window::Window()
{

}

Window::~Window()
{

}

bool Window::Init()
{
	WNDCLASSEX wClass = {};
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.style = CS_OWNDC;
	wClass.lpfnWndProc = WndProc;
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.hInstance = nullptr;
	wClass.hCursor = nullptr;
	wClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);;
	wClass.hbrBackground = nullptr;
	wClass.lpszMenuName = nullptr;
	wClass.lpszClassName = "Temp";

	if (!RegisterClassEx(&wClass)) return false;

	//if (!window) window = this;
	
	if (!(hWnd = CreateWindowEx(0, "Temp", "Aamir Akim", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 300, 300, 640, 480, nullptr, nullptr, nullptr, this))) return false;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	isRunning = true;

    return true;
}

bool Window::Broadcast()
{
	this->OnUpdate();

	MSG msg = {  };
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE) > 0)
	{
		if (msg.message == WM_QUIT)
		{
			break;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(1);

	return true;
}

bool Window::Release()
{
	if (!DestroyWindow(hWnd)) return false;

    return true;
}

bool Window::IsRunning()
{
	return isRunning;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	return rc;
}

void Window::SetHWND(HWND newHWND)
{
	hWnd = newHWND;
}

void Window::OnDestroy()
{
	isRunning = false;
}
