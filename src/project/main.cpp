# define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>

// Command IDs
#define IDM_CHANGE_BG 1
#define IDM_CHANGE_CURSOR 2
#define IDM_COMBINE_CONSOLE 3
#define IDM_CHOOSE_COLOR 4
#define IDM_CLEAR_SCREEN 5
#define IDM_LOAD_DATA 6

// Line Algorithms submenu IDs
#define IDM_LINE_DDA 7
#define IDM_LINE_MIDPOINT 8
#define IDM_LINE_PARAMETRIC 9

// Circle Algorithms submenu IDs
#define IDM_CIRCLE_DIRECT 10
#define IDM_CIRCLE_POLAR 11
#define IDM_CIRCLE_ITER_POLAR 12
#define IDM_CIRCLE_MIDPOINT 13
#define IDM_CIRCLE_MOD_MIDPOINT 14

#define IDM_FILL_CIRCLE_LINES 15
#define IDM_FILL_CIRCLE_CIRCLES 16
#define IDM_FILL_SQUARE_HERMIT 17
#define IDM_FILL_RECT_BEZIER 18
#define IDM_FILL_CONVEX_NONCONVEX 19
#define IDM_FILL_FLOOD_RECURSIVE 20
#define IDM_FILL_FLOOD_NONRECURSIVE 21
#define IDM_CARDINAL_SPLINE 22

// Ellipse Algorithms submenu IDs
#define IDM_ELLIPSE_DIRECT 23
#define IDM_ELLIPSE_POLAR 24
#define IDM_ELLIPSE_MIDPOINT 25

// Clipping algorithms (Rectangle)
#define IDM_CLIP_RECT_POINT 26
#define IDM_CLIP_RECT_LINE 27
#define IDM_CLIP_RECT_POLYGON 28

// Clipping algorithms (Square)
#define IDM_CLIP_SQUARE_POINT 29
#define IDM_CLIP_SQUARE_LINE 30

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (LOWORD(wp))
        {
        case IDM_CHANGE_BG:
            MessageBoxW(hwnd, L"Change Background to White Selected", L"Menu", MB_OK);
            break;
        case IDM_CHANGE_CURSOR:
            MessageBoxW(hwnd, L"Change Mouse Cursor Shape Selected", L"Menu", MB_OK);
            break;
        case IDM_COMBINE_CONSOLE:
            MessageBoxW(hwnd, L"Combine Console and Window Selected", L"Menu", MB_OK);
            break;
        case IDM_CHOOSE_COLOR:
        {
            std::cout << "Enter 3 integers for RGB color separated by spaces: ";
            int r, g, b;
            std::cin >> r >> g >> b;
            std::wstringstream woss;
            MessageBoxW(hwnd, L"Color Chosen", L"Menu", MB_OK);
            break;
        }
        case IDM_CLEAR_SCREEN:
            MessageBoxW(hwnd, L"Clear Screen Selected", L"Menu", MB_OK);
            break;
        case IDM_LOAD_DATA:
            MessageBoxW(hwnd, L"Load Data Selected", L"Menu", MB_OK);
            break;

            // Line Algorithms
        case IDM_LINE_DDA:
            MessageBoxW(hwnd, L"DDA Line Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_LINE_MIDPOINT:
            MessageBoxW(hwnd, L"Midpoint Line Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_LINE_PARAMETRIC:
            MessageBoxW(hwnd, L"Parametric Line Algorithm Selected", L"Menu", MB_OK);
            break;

            // Circle Algorithms
        case IDM_CIRCLE_DIRECT:
            MessageBoxW(hwnd, L"Direct Circle Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_CIRCLE_POLAR:
            MessageBoxW(hwnd, L"Polar Circle Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_CIRCLE_ITER_POLAR:
            MessageBoxW(hwnd, L"Iterative Polar Circle Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_CIRCLE_MIDPOINT:
            MessageBoxW(hwnd, L"Midpoint Circle Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_CIRCLE_MOD_MIDPOINT:
            MessageBoxW(hwnd, L"Modified Midpoint Circle Algorithm Selected", L"Menu", MB_OK);
            break;

        case IDM_FILL_CIRCLE_LINES:
            MessageBoxW(hwnd, L"Fill Circle with Lines Selected", L"Menu", MB_OK);
            break;
        case IDM_FILL_CIRCLE_CIRCLES:
            MessageBoxW(hwnd, L"Fill Circle with Other Circles Selected", L"Menu", MB_OK);
            break;
        case IDM_FILL_SQUARE_HERMIT:
            MessageBoxW(hwnd, L"Fill Square with Hermit Curve Selected", L"Menu", MB_OK);
            break;
        case IDM_FILL_RECT_BEZIER:
            MessageBoxW(hwnd, L"Fill Rectangle with Bezier Curve Selected", L"Menu", MB_OK);
            break;
        case IDM_FILL_CONVEX_NONCONVEX:
            MessageBoxW(hwnd, L"Convex and Non-Convex Filling Selected", L"Menu", MB_OK);
            break;
        case IDM_FILL_FLOOD_RECURSIVE:
            MessageBoxW(hwnd, L"Recursive Flood Fill Selected", L"Menu", MB_OK);
            break;
        case IDM_FILL_FLOOD_NONRECURSIVE:
            MessageBoxW(hwnd, L"Non-Recursive Flood Fill Selected", L"Menu", MB_OK);
            break;
        case IDM_CARDINAL_SPLINE:
            MessageBoxW(hwnd, L"Cardinal Spline Curve Selected", L"Menu", MB_OK);
            break;

            // Ellipse Algorithms
        case IDM_ELLIPSE_DIRECT:
            MessageBoxW(hwnd, L"Direct Ellipse Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_ELLIPSE_POLAR:
            MessageBoxW(hwnd, L"Polar Ellipse Algorithm Selected", L"Menu", MB_OK);
            break;
        case IDM_ELLIPSE_MIDPOINT:
            MessageBoxW(hwnd, L"Midpoint Ellipse Algorithm Selected", L"Menu", MB_OK);
            break;

            // Clipping Rectangle
        case IDM_CLIP_RECT_POINT:
            MessageBoxW(hwnd, L"Clip Rectangle - Point Selected", L"Menu", MB_OK);
            break;
        case IDM_CLIP_RECT_LINE:
            MessageBoxW(hwnd, L"Clip Rectangle - Line Selected", L"Menu", MB_OK);
            break;
        case IDM_CLIP_RECT_POLYGON:
            MessageBoxW(hwnd, L"Clip Rectangle - Polygon Selected", L"Menu", MB_OK);
            break;

            // Clipping Square
        case IDM_CLIP_SQUARE_POINT:
            MessageBoxW(hwnd, L"Clip Square - Point Selected", L"Menu", MB_OK);
            break;
        case IDM_CLIP_SQUARE_LINE:
            MessageBoxW(hwnd, L"Clip Square - Line Selected", L"Menu", MB_OK);
            break;

        default:
            break;
        }
        break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wp, lp);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
    WNDCLASSW wc = { 0 };
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = L"MyClass";
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowW(L"MyClass", L"HELLO WORLD",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 700,
        NULL, NULL, hInstance, NULL);

    // Create menu and submenus
    HMENU hMenubar = CreateMenu();

    // Main options menu (top-level)
    HMENU hMainMenu = CreatePopupMenu();

    AppendMenuW(hMainMenu, MF_STRING, IDM_CHANGE_BG, L"Change Background to White");
    AppendMenuW(hMainMenu, MF_STRING, IDM_CHANGE_CURSOR, L"Change Shape of Mouse");
    AppendMenuW(hMainMenu, MF_STRING, IDM_COMBINE_CONSOLE, L"Combine Console and Window");

    AppendMenuW(hMainMenu, MF_STRING, IDM_CHOOSE_COLOR, L"Choose Shape Color");

    AppendMenuW(hMainMenu, MF_STRING, IDM_CLEAR_SCREEN, L"Clear Screen");

    AppendMenuW(hMainMenu, MF_STRING, IDM_LOAD_DATA, L"Load Data from File");

    // Line Algorithms submenu
    HMENU hLineAlgos = CreatePopupMenu();
    AppendMenuW(hLineAlgos, MF_STRING, IDM_LINE_DDA, L"DDA");
    AppendMenuW(hLineAlgos, MF_STRING, IDM_LINE_MIDPOINT, L"Midpoint");
    AppendMenuW(hLineAlgos, MF_STRING, IDM_LINE_PARAMETRIC, L"Parametric");
    AppendMenuW(hMainMenu, MF_POPUP, (UINT_PTR)hLineAlgos, L"Line Algorithms");

    // Circle Algorithms submenu
    HMENU hCircleAlgos = CreatePopupMenu();
    AppendMenuW(hCircleAlgos, MF_STRING, IDM_CIRCLE_DIRECT, L"Direct");
    AppendMenuW(hCircleAlgos, MF_STRING, IDM_CIRCLE_POLAR, L"Polar");
    AppendMenuW(hCircleAlgos, MF_STRING, IDM_CIRCLE_ITER_POLAR, L"Iterative Polar");
    AppendMenuW(hCircleAlgos, MF_STRING, IDM_CIRCLE_MIDPOINT, L"Midpoint");
    AppendMenuW(hCircleAlgos, MF_STRING, IDM_CIRCLE_MOD_MIDPOINT, L"Modified Midpoint");
    AppendMenuW(hMainMenu, MF_POPUP, (UINT_PTR)hCircleAlgos, L"Circle Algorithms");

    AppendMenuW(hMainMenu, MF_STRING, IDM_FILL_CIRCLE_LINES, L"Fill Circle with Lines");
    AppendMenuW(hMainMenu, MF_STRING, IDM_FILL_CIRCLE_CIRCLES, L"Fill Circle with Other Circles");
    AppendMenuW(hMainMenu, MF_STRING, IDM_FILL_SQUARE_HERMIT, L"Fill Square with Hermit Curve");
    AppendMenuW(hMainMenu, MF_STRING, IDM_FILL_RECT_BEZIER, L"Fill Rectangle with Bezier Curve");
    AppendMenuW(hMainMenu, MF_STRING, IDM_FILL_CONVEX_NONCONVEX, L"Convex and Non-Convex Filling");
    AppendMenuW(hMainMenu, MF_STRING, IDM_FILL_FLOOD_RECURSIVE, L"Recursive Flood Fill");
    AppendMenuW(hMainMenu, MF_STRING, IDM_FILL_FLOOD_NONRECURSIVE, L"Non-Recursive Flood Fill");
    AppendMenuW(hMainMenu, MF_STRING, IDM_CARDINAL_SPLINE, L"Cardinal Spline Curve");

    // Ellipse Algorithms submenu
    HMENU hEllipseAlgos = CreatePopupMenu();
    AppendMenuW(hEllipseAlgos, MF_STRING, IDM_ELLIPSE_DIRECT, L"Direct");
    AppendMenuW(hEllipseAlgos, MF_STRING, IDM_ELLIPSE_POLAR, L"Polar");
    AppendMenuW(hEllipseAlgos, MF_STRING, IDM_ELLIPSE_MIDPOINT, L"Midpoint");
    AppendMenuW(hMainMenu, MF_POPUP, (UINT_PTR)hEllipseAlgos, L"Ellipse Algorithms");

    // Clipping algorithms rectangle submenu
    HMENU hClipRect = CreatePopupMenu();
    AppendMenuW(hClipRect, MF_STRING, IDM_CLIP_RECT_POINT, L"Clip Point");
    AppendMenuW(hClipRect, MF_STRING, IDM_CLIP_RECT_LINE, L"Clip Line");
    AppendMenuW(hClipRect, MF_STRING, IDM_CLIP_RECT_POLYGON, L"Clip Polygon");
    AppendMenuW(hMainMenu, MF_POPUP, (UINT_PTR)hClipRect, L"Clipping Rectangle");

    // Clipping algorithms square submenu
    HMENU hClipSquare = CreatePopupMenu();
    AppendMenuW(hClipSquare, MF_STRING, IDM_CLIP_SQUARE_POINT, L"Clip Point");
    AppendMenuW(hClipSquare, MF_STRING, IDM_CLIP_SQUARE_LINE, L"Clip Line");
    AppendMenuW(hMainMenu, MF_POPUP, (UINT_PTR)hClipSquare, L"Clipping Square");

    // Attach main menu bar
    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR)hMainMenu, L"Options");

    SetMenu(hwnd, hMenubar);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
