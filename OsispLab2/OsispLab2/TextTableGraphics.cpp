#include "TextTableGraphics.h"

TextTableGraphics::TextTableGraphics(HWND parentHWND, HDC parentHDC, TextTable* tableInfo)
{
	_parentHWND = parentHWND;
	_parentHDC = parentHDC;
	_tableInfo = tableInfo;

	short cellsAmount = tableInfo->GetRows() * tableInfo->GetColumns();
	_textBoxList = (HWND*)calloc(cellsAmount, sizeof(tableInfo));
}

void TextTableGraphics::Draw()
{
}
