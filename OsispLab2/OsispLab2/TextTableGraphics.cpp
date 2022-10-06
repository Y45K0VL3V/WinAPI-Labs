#include "TextTableGraphics.h"

TextTableGraphics::TextTableGraphics()
{
}

TextTableGraphics::TextTableGraphics(HWND parentHWND, TextTable* tableInfo)
{
	_parentHWND = parentHWND;
    //SetWindowSubclass(parentHWND, TableProc, 0, 0);

	_parentHDC = GetDC(parentHWND);
	_tableInfo = tableInfo;
	
	_tableWidth = CalcTableWidth(parentHWND);

	_cellsAmount = tableInfo->GetRows() * tableInfo->GetColumns();
	_textBoxList = (ResizableTextBox*)calloc(_cellsAmount, sizeof(ResizableTextBox));
	InitTextFields();
}

short TextTableGraphics::CalcTableWidth(HWND window)
{
	RECT windowRect;
	GetWindowRect(window, &windowRect);
	return windowRect.right - windowRect.left - 15;
}

void TextTableGraphics::UpdateTableWidth()
{
	short newWidth = CalcTableWidth(_parentHWND);
	if (newWidth != _tableWidth)
	{
		_tableWidth = newWidth;
		for (short i = 0; i < _cellsAmount; i++)
			_textBoxList[i].Resize();
	}

}

void TextTableGraphics::Draw(char** initData)
{
	UpdateTableWidth();

	char columnAmount = _tableInfo->GetColumns();
	int columnWidth = _tableWidth / columnAmount;

	int currPosY = 0;
	int maxHeightInRow = 0;
	for (short i = 0; i < _cellsAmount; i++)
	{
		if (initData != nullptr)
		{
			_textBoxList[i] = ResizableTextBox(_parentHWND, columnWidth * (i % columnAmount), currPosY, columnWidth, 100);

			wchar_t* textBuf = (wchar_t*)calloc(strlen(initData[i]) + 1, sizeof(wchar_t));
			mbstowcs(textBuf, initData[i], strlen(initData[i]) + 1);
			SetWindowText(_textBoxList[i].TextBoxWindow, textBuf);
			_textBoxList[i].Resize();
		}

		RECT currTextBoxRect;
		GetWindowRect(_textBoxList[i].TextBoxWindow, &currTextBoxRect);
		int currHeight = currTextBoxRect.bottom - currTextBoxRect.top;
		if (currHeight > maxHeightInRow) maxHeightInRow = currHeight;


		if ((i + 1) % columnAmount == 0)
		{
			for (short j = i; j >= i - columnAmount + 1; j--)
				SetWindowPos(_textBoxList[j].TextBoxWindow, NULL, _tableWidth - (i - j + 1) * columnWidth, currPosY, columnWidth, maxHeightInRow, NULL);

			currPosY += maxHeightInRow;
			maxHeightInRow = 0;
		}
	}
}

void TextTableGraphics::InitTextFields()
{
	char** initData = _tableInfo->GetInitData();
	Draw(initData);
}
