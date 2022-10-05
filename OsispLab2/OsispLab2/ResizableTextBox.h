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
private:
	//SUBCLASSPROC TextBoxProc;
	//LRESULT CALLBACK TextBoxProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
};

