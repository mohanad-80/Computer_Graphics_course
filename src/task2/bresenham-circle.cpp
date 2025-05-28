/**
 * @file bresenham-circle.cpp
 *
 * * running command:
 * g++ ./bresenham-circle.cpp -o bresenham-circle -mwindows && ./bresenham-circle.exe
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <Windows.h>
#include <cmath>

int xs, ys, xe, ye, r; // Declare global variables for start and end coordinates
int num_of_clicks = 0;

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

void draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc - y, yc - x, color);
}

void DrawCircleBresenham(HDC hdc, int xc, int yc, int r, COLORREF color)
{
    int x = 0, y = r;
    int d = 1 - r; // approximation
    int d1 = 3, d2 = 5 - 2 * r;
    draw8Points(hdc, xc, yc, x, y, color);
    while (x < y)
    {
        if (d >= 0)
        {
            d += d2;
            d2 += 4;
            y--;
        }
        else
        {
            d += d1;
            d2 += 2;
        }
        d1 += 2;
        x++;

        draw8Points(hdc, xc, yc, x, y, color);
    }
}

LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    RECT rect;
    switch (m)
    {
    case WM_LBUTTONDOWN:
        if (num_of_clicks == 0)
        {
            xs = LOWORD(lp);
            ys = HIWORD(lp);
            num_of_clicks++;
        }
        else if (num_of_clicks == 1)
        {
            xe = LOWORD(lp);
            ye = HIWORD(lp);
            r = sqrt(pow(xe - xs, 2) + pow(ye - ys, 2));
            hdc = GetDC(hwnd);
            DrawCircleBresenham(hdc, xs, ys, r, RGB(0, 255, 0));
            DrawLineBresenham(hdc, xs - r, ys, xs + r, ys, RGB(0, 255, 0));
            DrawLineBresenham(hdc, xs, ys - r, xs, ys + r, RGB(0, 255, 0));
            int x = round(r * cos(45 * M_PI / 180.0));
            int y = round(r * sin(45 * M_PI / 180.0));
            DrawLineBresenham(hdc, xs - x, ys - y, xs + x, ys + y, RGB(0, 255, 0));
            DrawLineBresenham(hdc, xs - x, ys + y, xs + x, ys - y, RGB(0, 255, 0));
            ReleaseDC(hwnd, hdc);
            num_of_clicks = 0;
        }
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