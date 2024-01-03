#include "Window.h"

Window::Window():m_hwnd(nullptr), m_isRun(false)
{
}

/**
* The declaration LRESULT CALLBACK WNDPROC(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) represents 
	the window procedure, or simply, the callback function that handles messages sent to a window 
	in a Windows application.
	Let's break down the parameters:

* 1.HWND hwnd: A handle to the window that receives the message. 
	This identifies the specific window instance to which the message is directed.

* 2. UINT msg: An unsigned integer value representing the message identifier. 
	This code uniquely identifies the type of message being sent.

* 3. WPARAM wparam: A parameter of type WPARAM, which stands for "word parameter."
	It contains additional message-specific information. The meaning of this parameter 
	varies depending on the message being processed.

* 4. LPARAM lparam: A parameter of type LPARAM, which stands for "long parameter." 
	Similar to wparam, it contains additional message-specific information. 
	The interpretation of this parameter depends on the message being processed.

* 5. LRESULT: A long integer value that is used as the return type for the window procedure. 
	The meaning of the return value depends on the specific message being processed.
**/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return NULL;
}

bool Window::init()
{
	/* *
	* `WNDCLASSEX` is a structure in the Windows API(Application Programming Interface)
	* that defines the attributes and characteristics of a window class. 
	* */


	// Setting up WNDCLASSEX object
	WNDCLASSEX wc;

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;			/* Extra bytes to allocate for the class and instance.
									* These can be used to store additional data associated
										with the class or instances of the class. */

	wc.cbSize = sizeof(WNDCLASSEX);	// The size of the structure, in bytes
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; /* A handle to the class background brush. It specifies the background color for the class.
											  * COLOR_WINDOW is a predefined constant in the Windows API that represents the default color of the window background. It's a system color constant, and its value corresponds to the system's current window background color.
											  * (HBRUSH) is a typecast.It's used here to convert the constant COLOR_WINDOW to a handle to a brush (HBRUSH). This is necessary because the hbrBackground member expects a handle to a brush.*/
	
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);	// A handle to the class cursor. This cursor is used when the mouse is over a window of this class.
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // A handle to the class icon. This icon is associated with the class and is displayed when the user presses ALT+TAB to switch between applications.
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL; // A handle to the instance that contains the window procedure for the class.

	wc.lpszClassName = L"MyWindowClass"; //A pointer to a null-terminated string that specifies the name of the class.
	wc.lpszMenuName = L"";

	wc.style = NULL;
	wc.lpfnWndProc = &WndProc; //A pointer to the window procedure.This function is called to handle messages sent to windows of this class.

	// If the registration of class will fail, the function will return false
	if (!::RegisterClassEx(&wc))
	{
		return false;
	}


	// creation of the window
	m_hwnd = ::CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,			// Extended window style
		L"MyWindowClass",				// Class name
		L"DirectX Application",			// Window Title
		WS_OVERLAPPEDWINDOW,			// Window Style
		CW_USEDEFAULT, CW_USEDEFAULT,	// Initial position (X,Y)
		1024, 768,						// Initial size (width, height)
		NULL,							// Parent window handle (no parent)
		NULL,							// Menu handle (no menu)
		NULL,							// Instance handle (no instance specific data)
		this							// Pointer to user data (in this case, a pointer to the Window instance)
	);

	//if the creation fail return false
	if (!m_hwnd)
	{
		return false;
	}

	::ShowWindow(m_hwnd, SW_SHOW);	// a Windows API function used to set the show state of a window.
	::UpdateWindow(m_hwnd);			/*  a Windows API function used to ensure that the client area of a window 
										is updated by sending a WM_PAINT message to the window's procedure.*/

	//set this flag to true to indicate that the window is initialized and running
	m_isRun = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	this->onUpdate();
	Sleep(1);
	return true;
}

bool Window::release()
{
	if (!::DestroyWindow(m_hwnd))
	{
		return false;
	}
	return true;
}

bool Window::isRun()
{
	return m_isRun;
}

Window::~Window()
{
}

void Window::onCreate()
{
}

void Window::onDestroy()
{
	m_isRun = false;
}

void Window::onUpdate()
{
}
