#include "ResizableTextBox.h"

void ResizeTextBox(HWND hWnd)
{
    RECT textBoxRect;
    GetWindowRect(hWnd, &textBoxRect);
    int width = textBoxRect.right - textBoxRect.left;
    HDC textBoxHDC = GetDC(hWnd);

    wchar_t text[1024];
    GetWindowText(hWnd, text, 1024);
    DrawText(textBoxHDC, text, wcslen(text), &textBoxRect, DT_CALCRECT | DT_WORDBREAK | DT_LEFT | DT_EDITCONTROL);
    textBoxRect.right = textBoxRect.left + width;
    SetWindowPos(hWnd, NULL, 0, 0, textBoxRect.right - textBoxRect.left, textBoxRect.bottom - textBoxRect.top + 4, SWP_NOMOVE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_NOTIFY:
            break;
        case WM_KILLFOCUS:
        {
            ResizeTextBox(hWnd);
            SendMessage(GetParent(hWnd), WM_COMMAND, LPARAM(6666), NULL);
        }
        break;
        case WM_NCDESTROY:
            RemoveWindowSubclass(hWnd, WinProc, 0);
            return 0;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

ResizableTextBox::ResizableTextBox(HWND parentHWND, int x, int y, int width, int height)
{
    TextBoxWindow = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL, x, y, width, height, parentHWND, NULL, NULL, NULL);
    SetWindowSubclass(TextBoxWindow, WinProc, 0, 0);
}

void ResizableTextBox::Resize()
{
    ResizeTextBox(TextBoxWindow);
}


