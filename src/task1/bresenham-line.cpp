/**
 * @file bresenham-line.cpp
 *
 * running command:
 * g++ ./bresenham-line.cpp -o bresenham-line -mwindows && ./bresenham-line.exe
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <Windows.h>

int xs, ys, xe, ye; // Declare global variables for start and end coordinates

int Round(double x)
{
    return (int)(x + 0.5);
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
    return;
}

void DrawLineBresenham(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    bool steep = abs(y2 - y1) > abs(x2 - x1);

    // If the line is steep, swap x and y coordinates.
    // now x represent y and vice versa meaning that the
    // slope is inverted.
    if (steep)
    {
        swap(x1, y1);
        swap(x2, y2);
    }

    // Ensure left-to-right drawing
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int yStep = (y1 < y2) ? 1 : -1; // Determine the y-direction

    int d = 2 * dy - dx;
    int d1 = 2 * dy;
    int d2 = 2 * (dy - dx);

    int x = x1;
    int y = y1;

    while (x <= x2)
    {
        if (steep)
            SetPixel(hdc, y, x, c); // Swap back if steep
        else
            SetPixel(hdc, x, y, c);

        if (d > 0)
        {
            y += yStep;
            d += d2;
        }
        else
        {
            d += d1;
        }

        x++;
    }
}

LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    RECT rect;
    switch (m)
    {
    case WM_LBUTTONDOWN:
        xs = LOWORD(lp);
        ys = HIWORD(lp);
        break;
    case WM_LBUTTONUP:
        xe = LOWORD(lp);
        ye = HIWORD(lp);
        hdc = GetDC(hwnd);
        DrawLineBresenham(hdc, xs, ys, xe, ye, RGB(0, 255, 0));
        ReleaseDC(hwnd, hdc);
        break;
    case WM_RBUTTONDOWN:
        hdc = GetDC(hwnd);
        GetClientRect(hwnd, &rect);
        FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        ReleaseDC(hwnd, hdc);
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, m, wp, lp);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR cmd, int nsh)
{
    WNDCLASSW wc; // Use WNDCLASSW
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.lpszClassName = L"MyClass";
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hi;
    RegisterClassW(&wc);                                                                                                                                        // Use RegisterClassW
    HWND hwnd = CreateWindowW(L"MyClass", L"Hello World!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hi, 0); // Use CreateWindowW
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}