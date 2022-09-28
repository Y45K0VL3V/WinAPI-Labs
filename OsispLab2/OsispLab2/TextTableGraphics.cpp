#include "TextTableGraphics.h"

TextTableGraphics::TextTableGraphics(HWND parentHWND, HDC parentHDC, TextTable* tableInfo)
{
	_parentHWND = parentHWND;
	_parentHDC = parentHDC;
	_tableInfo = tableInfo;
}

void TextTableGraphics::Draw()
{
}
