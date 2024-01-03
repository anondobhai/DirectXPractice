#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	
	// Initialize
	bool init();
	bool broadcast();

	// release
	bool release();
	bool isRun();
	~Window();

	//EVENTS
	virtual void onCreate();
	virtual void onDestroy();
	virtual void onUpdate();

private:
	HWND m_hwnd;
	bool m_isRun;
};

