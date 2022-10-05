#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "string.h"
#include "TextTable.h"
#include "ResizableTextBox.h"

class TextTableGraphics
{
public:
	TextTableGraphics();
	TextTableGraphics(HWND parentHWND, TextTable* tableInfo);
	void Draw();

	short GetTableWidth() { return _tableWidth; };
	short GetTableHeight() { return _tableHeight; };

	ResizableTextBox* GetTextFields() { return _textBoxList; };
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

	ResizableTextBox* _textBoxList;

	void InitTextFields(short cellsAmount);
	short GetTableWidthFromRect(RECT windowRect);
};

