// OsispLab1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "OsispLab1.h"
#include "windowsx.h"
#include "MoveableRectangle.h"

#define MAX_LOADSTRING 100
#define MOVE_TIMER 1;

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

//enum VerticalDirection
//{
//    Up = -1,
//    Down = 1,
//};
//
//enum HorizontalDirection
//{
//    Left = -1,
//    Right = 1,
//};
//
//struct MoveDirection {
//
//};

RECT WindowRect;
MoveableRectangle MoveRect(10,10,150,150);

//BOOL IsNewSpeedValid(signed char oldSpeed, signed short speedChangeValue)
//{
//    signed newSpeed = oldSpeed + speedChangeValue;
//    return (newSpeed <= 100 && newSpeed >= 0);
//}

//signed char RectXSpeed = 0;
//signed char ChangeXSpeed(signed short dx)
//{
//    if (IsNewSpeedValid(RectXSpeed, dx))
//        RectXSpeed += dx;
//    
//    return RectXSpeed;
//}
//
//signed char RectYSpeed = 0;
//signed char ChangeYSpeed(signed short dy)
//{
//    if (IsNewSpeedValid(RectYSpeed, dy))
//        RectYSpeed += dy;
//
//    return RectYSpeed;
//}


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

    //if (*xChange != oldXChange) ChangeXSpeed(-2 * RectXSpeed);
    //if (*yChange != oldYChange) ChangeYSpeed(-2 * RectYSpeed);

    return (*xChange != oldXChange || *yChange != oldYChange);
}

void MoveRectangle(HWND hWnd, LPRECT rectangle, LONG xChange, LONG yChange)
{
    CheckOutBorderMove(rectangle, &xChange, &yChange);

    OffsetRect(rectangle, xChange, yChange);
    InvalidateRect(hWnd, NULL, TRUE);
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
    int nTimerId = SetTimer(hWnd, 1, 1, NULL);

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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            FillRect(hdc, &MoveRect.RectObject, (HBRUSH)CreateSolidBrush(RGB(235,125,64)));
            //Graphics::DrawImage();

            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_LBUTTONDOWN:
    {
        CurrCursorPos = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
        if ((CurrCursorPos.x >= MoveRect.RectObject.left && CurrCursorPos.x <= MoveRect.RectObject.right) &&
            (CurrCursorPos.y >= MoveRect.RectObject.top && CurrCursorPos.y <= MoveRect.RectObject.bottom))
            IsRectCaptured = TRUE;
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

        //// Decrease horizontal speed.
        //case VK_NUMPAD4:
        //    ChangeXSpeed(-2);
        //    break;
        //// Increase horizontal speed.
        //case VK_NUMPAD6:
        //    ChangeXSpeed(2);
        //    break;
        //// Decrease vertical speed.
        //case VK_NUMPAD2:
        //    ChangeYSpeed(-2);
        //    break;
        //// Increase vertical speed.
        //case VK_NUMPAD8:
        //    ChangeYSpeed(2);
        //    break;
        case VK_SPACE:
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
        PostQuitMessage(0);
        break;
    }
    case WM_TIMER:
    {
        //MoveRectangle(hWnd, &MoveRect, RectXSpeed, RectYSpeed);
    }
    break;
    case WM_SIZE:
    {
        GetClientRect(hWnd, &WindowRect);
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
