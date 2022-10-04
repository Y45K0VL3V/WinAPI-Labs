#include "TextTableGraphics.h"

TextTableGraphics::TextTableGraphics()
{
}

TextTableGraphics::TextTableGraphics(HWND parentHWND, TextTable* tableInfo)
{
	_parentHWND = parentHWND;
	_parentHDC = GetDC(parentHWND);
	_tableInfo = tableInfo;

	short cellsAmount = tableInfo->GetRows() * tableInfo->GetColumns();
	_textBoxList = (ResizableTextBox*)calloc(cellsAmount, sizeof(ResizableTextBox));
}

void TextTableGraphics::Draw()
{

}
