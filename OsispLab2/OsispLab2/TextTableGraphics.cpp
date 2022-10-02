#include "TextTableGraphics.h"

TextTableGraphics::TextTableGraphics(HWND parentHWND, HDC parentHDC, TextTable* tableInfo)
{
	_parentHWND = parentHWND;
	_parentHDC = parentHDC;
	_tableInfo = tableInfo;

	short cellsAmount = tableInfo->GetRows() * tableInfo->GetColumns();
	_textBoxList = (ResizableTextBox*)calloc(cellsAmount, sizeof(ResizableTextBox));
}

void TextTableGraphics::Draw()
{
}
