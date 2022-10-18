#pragma once
#pragma comment(lib, "comctl32.lib")

#include "framework.h"
#include "commctrl.h"

class ResizableTextBox
{
public:
	ResizableTextBox(HWND parentHWND, double x, double y, double width, double height);

	void Resize();
	LONG GetTrueHeight();

	HWND TextBoxWindow;
};

