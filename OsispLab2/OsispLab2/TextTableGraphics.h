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
	void Draw(char** initData);

	double GetTableWidth() { return _tableWidth; };
	double GetTableHeight() { return _tableHeight; };

	ResizableTextBox* GetTextFields() { return _textBoxList; };
private:
	double _tableWidth;
	double _tableHeight;

	HWND _parentHWND;
	HDC _parentHDC;
	TextTable* _tableInfo;

	short _cellsAmount;
	ResizableTextBox* _textBoxList;

	void InitTextFields();
	double CalcTableWidth(HWND window);
	void UpdateTableWidth();
};

