#pragma once
#include "Window.h"

class AppWindow: public Window
{
public:
	AppWindow();
	virtual void onCreate();
	virtual void onDestroy();
	virtual void onUpdate();
	~AppWindow();
};

