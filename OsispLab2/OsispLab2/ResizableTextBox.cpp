#include "ResizableTextBox.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_NOTIFY:
            break;
        case WM_COMMAND:
        {
            int wmId = HIWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
                case EN_CHANGE:
                {
                    RECT textBoxRect;
                    GetWindowRect(hWnd, &textBoxRect);
                    HDC textBoxHDC = GetDC(hWnd);

                    wchar_t text[1024];
                    SendMessage(hWnd, WM_GETTEXT, 1024, LPARAM(text));
                    DrawText(textBoxHDC, text, wcslen(text), &textBoxRect, DT_CALCRECT | DT_LEFT);
                    SetWindowPos(hWnd, NULL, 0, 0, textBoxRect.right - textBoxRect.left, textBoxRect.bottom - textBoxRect.top + 4, SWP_NOMOVE);

                    break;
                }
            }
        }
        break;
        case WM_NCDESTROY:
            RemoveWindowSubclass(hWnd, WndProc, 0);
            return 0;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

ResizableTextBox::ResizableTextBox(HWND parentHWND, int x, int y, int width, int height)
{
    TextBoxWindow = CreateWindow(L"Edit", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL, x, y, width, height, parentHWND, NULL, NULL, NULL);
    SetWindowSubclass(TextBoxWindow, WndProc, 0, 0);
}
