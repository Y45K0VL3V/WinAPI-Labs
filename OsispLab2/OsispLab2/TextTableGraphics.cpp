#include "TextTableGraphics.h"

TextTableGraphics::TextTableGraphics()
{
}

TextTableGraphics::TextTableGraphics(HWND parentHWND, TextTable* tableInfo)
{
	_parentHWND = parentHWND;
	_parentHDC = GetDC(parentHWND);
	_tableInfo = tableInfo;
	
	RECT windowRect;
	GetWindowRect(_parentHWND, &windowRect);
	_tableWidth = windowRect.right - windowRect.left;


	short cellsAmount = tableInfo->GetRows() * tableInfo->GetColumns();
	_textBoxList = (ResizableTextBox*)calloc(cellsAmount, sizeof(ResizableTextBox));
	InitTextFields(cellsAmount);
}



void TextTableGraphics::Draw()
{

}

void TextTableGraphics::InitTextFields(short cellsAmount)
{
	char** initData = _tableInfo->GetInitData();
	char columnAmount = _tableInfo->GetColumns();
	int columnWidth = _tableWidth / columnAmount;

	int currPosY = 0;
	for (short i = 0; i < cellsAmount; i++)
	{
		_textBoxList[i] = ResizableTextBox(_parentHWND, columnWidth * (i % columnAmount), currPosY, columnWidth, 100);
		
		wchar_t* textBuf = (wchar_t*)calloc(strlen(initData[i]) + 1, sizeof(wchar_t));
		mbstowcs(textBuf, initData[i], strlen(initData[i]) + 1);
		SetWindowText(_textBoxList[i].TextBoxWindow, textBuf);

		if ((i + 1) % columnAmount == 0)
		{
			currPosY += 100;
		}
	}
}
