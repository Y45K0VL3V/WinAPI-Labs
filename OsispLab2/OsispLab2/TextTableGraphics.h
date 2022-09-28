#pragma once

#include "framework.h"
#include "string.h"
#include <string>
#include "TextTable.h"

class TextTableGraphics
{
public:
	TextTableGraphics(HWND parentHWND, HDC parentHDC, TextTable* tableInfo);
	void Draw();

private:
	HWND _parentHWND;
	HDC _parentHDC;
	TextTable* _tableInfo;

	HWND* _textBoxList;
};

