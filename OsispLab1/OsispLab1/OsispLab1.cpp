// OsispLab1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "OsispLab1.h"
#include "windowsx.h"
#include "MoveableRectangle.h"
#include "resource.h"

#pragma comment(lib, "Msimg32.lib")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.    

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OSISPLAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OSISPLAB1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OSISPLAB1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OSISPLAB1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

const int MOVE_TIMER = 1;

#pragma region Double bufferization

HDC HdcBuffer;
HANDLE HandleBuffer;

VOID InitializeBuffer(HWND hWnd, int width, int height)
{
    HDC hdcWindow;
    hdcWindow = GetDC(hWnd);
    HdcBuffer = CreateCompatibleDC(hdcWindow);
    HandleBuffer = CreateCompatibleBitmap(hdcWindow, width, height);
    SaveDC(HdcBuffer);
    SelectObject(HdcBuffer, HandleBuffer);
    ReleaseDC(hWnd, hdcWindow);
}

VOID FinalizeBuffer()
{
    if (HdcBuffer)
    {
        RestoreDC(HdcBuffer, -1);
        DeleteObject(HandleBuffer);
        DeleteObject(HdcBuffer);
    }
}
#pragma endregion

RECT WindowRect;

#pragma region Moving rect interaction.

MoveableRectangle MoveRect(10,10,300,300);

HANDLE RectanglePictureHandler;
BITMAP RectangleBmp;
BOOL IsRectShow = TRUE;

POINT CurrCursorPos;
BOOL IsRectCaptured = FALSE;

BOOL CheckOutBorderMove(LPRECT rectangle, LONG* xChange, LONG* yChange)
{
    LONG oldXChange = *xChange;
    LONG oldYChange = *yChange;

    if (rectangle->top + *yChange <= WindowRect.top)
        *yChange = WindowRect.top - rectangle->top;

    if (rectangle->bottom + *yChange >= WindowRect.bottom)
        *yChange = WindowRect.bottom - rectangle->bottom;

    if (rectangle->left + *xChange <= WindowRect.left)
        *xChange = WindowRect.left - rectangle->left;

    if (rectangle->right + *xChange >= WindowRect.right)
        *xChange = WindowRect.right - rectangle->right;

    if (*xChange != oldXChange) 
        MoveRect.Direction.HorizontalDirection = static_cast<HorizontalDirectionType>(static_cast<char>(MoveRect.Direction.HorizontalDirection) * -1);
    if (*yChange != oldYChange) 
        MoveRect.Direction.VerticalDirection = static_cast<VerticalDirectionType>(static_cast<char>(MoveRect.Direction.VerticalDirection) * -1);

    return (*xChange != oldXChange || *yChange != oldYChange);
}

VOID MoveRectangle(HWND hWnd, LPRECT rectangle, LONG xChange, LONG yChange)
{
    CheckOutBorderMove(rectangle, &xChange, &yChange);

    OffsetRect(rectangle, xChange, yChange);
    InvalidateRect(hWnd, NULL, FALSE);
}

#pragma endregion

BOOL IsTimerStopped = TRUE;
VOID InvertTimerState(HWND hWnd, int timerId)
{
    if (IsTimerStopped)
    {
        SetTimer(hWnd, timerId, 10, NULL);
        IsTimerStopped = FALSE;
    }
    else
    {
        KillTimer(hWnd, timerId);
        IsTimerStopped = TRUE;
    }
}

VOID DrawObject(HWND hWnd)
{
    HBRUSH brushWindow = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(HdcBuffer, &WindowRect, brushWindow);

    if (IsRectShow)
    {
        HBRUSH brush = CreateSolidBrush(RGB(235, 125, 64));
        FillRect(HdcBuffer, &MoveRect.RectObject, brush);
        DeleteObject(brush);
    }
    else
    {
        HDC hMemDc = CreateCompatibleDC(HdcBuffer);
        HBITMAP hBmp = (HBITMAP)SelectObject(hMemDc, RectanglePictureHandler);
        if (hBmp)
        {
            SetMapMode(hMemDc, GetMapMode(HdcBuffer));
            TransparentBlt(HdcBuffer, MoveRect.RectObject.left, MoveRect.RectObject.top,
                MoveRect.RectObject.right - MoveRect.RectObject.left, MoveRect.RectObject.bottom - MoveRect.RectObject.top,
                hMemDc, 0, 0, RectangleBmp.bmWidth, RectangleBmp.bmHeight, RGB(255, 255, 255));
            SelectObject(hMemDc, hBmp);
        }

        DeleteDC(hMemDc);
    }

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    BitBlt(hdc, 0, 0, WindowRect.right, WindowRect.bottom, HdcBuffer, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
       return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    GetClientRect(hWnd, &WindowRect);
    InvertTimerState(hWnd, MOVE_TIMER);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        RectanglePictureHandler = LoadImage(NULL, L"picture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
        GetObject(RectanglePictureHandler, sizeof(RectangleBmp), &RectangleBmp);
    }
    break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        DrawObject(hWnd);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        CurrCursorPos = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        if ((CurrCursorPos.x >= MoveRect.RectObject.left && CurrCursorPos.x <= MoveRect.RectObject.right) &&
            (CurrCursorPos.y >= MoveRect.RectObject.top && CurrCursorPos.y <= MoveRect.RectObject.bottom))
        {
            KillTimer(hWnd, MOVE_TIMER);

            IsRectCaptured = TRUE;
        }
    }
    break;
    case WM_MOUSEMOVE:
    {
        if (IsRectCaptured)
        {
            POINT prevPoint = CurrCursorPos;
            GetCursorPos(&CurrCursorPos);
            ScreenToClient(FindWindowA(NULL, "OsispLab1"), &CurrCursorPos);

            MoveRectangle(hWnd, &MoveRect.RectObject, CurrCursorPos.x - prevPoint.x, CurrCursorPos.y - prevPoint.y);
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        if(!IsTimerStopped)
            SetTimer(hWnd, MOVE_TIMER, 10, NULL);

        IsRectCaptured = FALSE;
    }
    break;
    case WM_KEYDOWN:
    {
        switch (wParam) {
        case VK_LEFT:
            MoveRectangle(hWnd, &MoveRect.RectObject, -10, 0);
            break;

        case VK_RIGHT:
            MoveRectangle(hWnd, &MoveRect.RectObject, 10, 0);
            break;

        case VK_UP:
            MoveRectangle(hWnd, &MoveRect.RectObject, 0, -10);
            break;

        case VK_DOWN:
            MoveRectangle(hWnd, &MoveRect.RectObject, 0, 10);
            break;

        // Left horizontal direction.
        case VK_NUMPAD4:
            MoveRect.Direction.HorizontalDirection = HorizontalDirectionType::Left;
            break;
        // Right horizontal direction.
        case VK_NUMPAD6:
            MoveRect.Direction.HorizontalDirection = HorizontalDirectionType::Right;
            break;
        // Down vertical direction.
        case VK_NUMPAD2:
            MoveRect.Direction.VerticalDirection = VerticalDirectionType::Down;
            break;
        // Up vertical direction.
        case VK_NUMPAD8:
            MoveRect.Direction.VerticalDirection = VerticalDirectionType::Up;
            break;

        // Clear direction.
        case VK_NUMPAD5:
        {
            MoveRect.Direction.VerticalDirection = VerticalDirectionType::None;
            MoveRect.Direction.HorizontalDirection = HorizontalDirectionType::None;
            break;
        }

        // Increase speed.
        case VK_ADD:
            MoveRect.ChangeSpeed(1);
            break;
        // Decrease speed.
        case VK_SUBTRACT:
            MoveRect.ChangeSpeed(-1);
            break;
        case VK_BACK:
            MoveRect.ChangeSpeed(MoveRect.GetSpeed() * -1);
            break;
        // Pause rect moving.
        case VK_SPACE:
        {
            if(!IsRectCaptured)
                InvertTimerState(hWnd, MOVE_TIMER);

            break;
        }

        case VK_TAB:
            IsRectShow = !IsRectShow;
            DrawObject(hWnd);
            break;
        default:
            break;
        }
    }
    break;
    case WM_MOUSEWHEEL:
    {
        BOOL isShiftPressed = (BOOL)GetAsyncKeyState(VK_SHIFT);

        if(!isShiftPressed)
            ((short)HIWORD(wParam) < 0) ? MoveRectangle(hWnd, &MoveRect.RectObject, 0, 10) : MoveRectangle(hWnd, &MoveRect.RectObject, 0, -10);
        else
            ((short)HIWORD(wParam) < 0) ? MoveRectangle(hWnd, &MoveRect.RectObject, -10, 0) : MoveRectangle(hWnd, &MoveRect.RectObject, 10, 0);
    }
    break;
    case WM_DESTROY:
    {
        FinalizeBuffer();
        PostQuitMessage(0);
        break;
    }
    case WM_TIMER:
    {
        MoveRectangle(hWnd, &MoveRect.RectObject, MoveRect.GetXVectorSpeed(), MoveRect.GetYVectorSpeed());
    }
    break;
    case WM_SIZE:
    {
        GetClientRect(hWnd, &WindowRect);
        FinalizeBuffer();
        InitializeBuffer(hWnd, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top);
        MoveRectangle(hWnd, &MoveRect.RectObject, 0, 0);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
