#pragma once
#pragma comment(lib, "comctl32.lib")

#include "framework.h"
#include "commctrl.h"

class ResizableTextBox
{
public:
	ResizableTextBox(HWND parentHWND, int x, int y, int width, int height);

	void Resize();

	HWND TextBoxWindow;
};

