#include "TextTableGraphics.h"

//LRESULT CALLBACK TableProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
//{
//    switch (uMsg)
//    {
//    case WM_NOTIFY:
//        break;
//    case WM_COMMAND:
//    {
//        int wmId = HIWORD(wParam);
//        // Parse the menu selections:
//        switch (wmId)
//        {
//            case EN_CHANGE:
//            {
//                //short cellsAmount = tableInfo->GetRows() * tableInfo->GetColumns();
//                for (short i = 0; i < 30; i++)
//                {
//                    RECT textBoxRect;
//                    GetWindowRect(hWnd, &textBoxRect);
//                    HDC textBoxHDC = GetDC(hWnd);
//
//                    wchar_t text[1024];
//                    SendMessage(hWnd, WM_GETTEXT, 1024, LPARAM(text));
//                    DrawText(textBoxHDC, text, wcslen(text), &textBoxRect, DT_CALCRECT | DT_LEFT);
//                    SetWindowPos(hWnd, NULL, 0, 0, textBoxRect.right - textBoxRect.left, textBoxRect.bottom - textBoxRect.top + 4, SWP_NOMOVE);
//                }
//                break;
//            }
//        }
//    }
//    break;
//    case WM_NCDESTROY:
//        RemoveWindowSubclass(hWnd, TableProc, 0);
//        return 0;
//    }
//    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
//}

TextTableGraphics::TextTableGraphics()
{
}

TextTableGraphics::TextTableGraphics(HWND parentHWND, TextTable* tableInfo)
{
	_parentHWND = parentHWND;
    //SetWindowSubclass(parentHWND, TableProc, 0, 0);

	_parentHDC = GetDC(parentHWND);
	_tableInfo = tableInfo;
	
	RECT windowRect;
	GetWindowRect(_parentHWND, &windowRect);
	_tableWidth = GetTableWidthFromRect(windowRect);

	short cellsAmount = tableInfo->GetRows() * tableInfo->GetColumns();
	_textBoxList = (ResizableTextBox*)calloc(cellsAmount, sizeof(ResizableTextBox));
	InitTextFields(cellsAmount);
}

short TextTableGraphics::GetTableWidthFromRect(RECT windowRect)
{
	return windowRect.right - windowRect.left - 15;
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
