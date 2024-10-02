#include "Window.h"
#include "WindowsMessageMap.h"


Window::Window() : width (640), height(480), isRunning(false),
	windowClassName("WindowClass"), windowStyles(WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU), parentHwnd(nullptr), hWnd(nullptr)
{

}

Window::~Window()
{

}

bool Window::Init(int width, int height, std::string windowName)
{
	this->width = width;
	this->height = height;

	WNDCLASSEX wClass = {};
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.style = CS_OWNDC;
	wClass.lpfnWndProc = StaticWndProc; 
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.hInstance = GetModuleHandleA(nullptr);
	wClass.hCursor = nullptr;
	wClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);;
	wClass.hbrBackground = nullptr;
	wClass.lpszMenuName = nullptr;
	wClass.lpszClassName = windowClassName.c_str();

	if (!RegisterClassEx(&wClass))
	{
		return false;
	}

	windowSize;
	windowSize.left = 100;
	windowSize.right = width + windowSize.left;
	windowSize.top = 100;
	windowSize.bottom = height + windowSize.top;
	if (AdjustWindowRect(&windowSize, windowStyles, FALSE) == 0)
	{
		return false;
	}
	
	if (!(hWnd = CreateWindowEx(0, windowClassName.c_str(), windowName.c_str(), windowStyles, 
		CW_USEDEFAULT, CW_USEDEFAULT, windowSize.right - windowSize.left, windowSize.bottom - windowSize.top,
		parentHwnd, nullptr, GetModuleHandleA(nullptr), this)))
	{
		return false;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	isRunning = true;

    return true;
}

bool Window::Release()
{
	if (!UnregisterClass(windowClassName.c_str(), GetModuleHandleA(nullptr)))
	{
		// uncomment for DEBUG
		//TCHAR   lpBuffer[256] = TEXT("?");
		//FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,           // It´s a system error
		//		NULL,                                       // No string to be formatted needed
		//		GetLastError(),                             // Hey Windows: Please explain this error!
		//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Do it in the standard language
		//		lpBuffer,                                   // Put the message here
		//		255,                                        // Number of bytes to store the message
		//		NULL);
		//OutputDebugString(lpBuffer);
		return false;
	}

	// most likely Release() is called when window is already closed, so destroy might be unnecessary
	/*if (!DestroyWindow(hWnd))
	{
		return false;
	}*/

	return true;
}

bool Window::Update()
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

void Window::OnDestroy()
{
	isRunning = false;
}

LRESULT Window::StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// uncomment for DEBUG (also prints the Widnow Messages (msg) to the Output Tab)
	//static WindowsMessageMap mm;
	//OutputDebugString(mm(msg, lParam, wParam).c_str());


	Window* window = nullptr;

	switch (msg)
	{
		case WM_CREATE:
		{
			window = static_cast<Window*>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
			window->OnCreate(hWnd);
			break;
		}
		case WM_DESTROY:
		{
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			window->OnDestroy(); 
			PostQuitMessage(0); 
			break; 
		}
		default:
		{
			window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			if (window == nullptr) return DefWindowProc(hWnd, msg, wParam, lParam);
			break;
		}
	}

	return window->HandleWindowMessages(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleWindowMessages(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


	return DefWindowProc(hWnd, msg, wParam, lParam);
}
