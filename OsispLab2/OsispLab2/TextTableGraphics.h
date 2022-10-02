#pragma once

#include "framework.h"
#include "string.h"
#include "TextTable.h"

class TextTableGraphics
{
public:
	TextTableGraphics(HWND parentHWND, HDC parentHDC, TextTable* tableInfo);
	void Draw();


	short GetTableWidth() { return _tableWidth; };
	short GetTableHeight() { return _tableHeight; };

private:
	// x - horizontal coord. of left top point.
	short _x;
	// y - vertical coord. of left top point.
	short _y;

	short _tableWidth;
	short _tableHeight;

	HWND _parentHWND;
	HDC _parentHDC;
	TextTable* _tableInfo;

	HWND* _textBoxList;
};

