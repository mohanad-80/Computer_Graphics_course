#include <Windows.h>
#include <cmath>

int xc, yc, x, y, r;

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

void CircleBresenham(HDC hdc, int xc, int yc, int r, COLORREF color)
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
  switch (m)
  {
  case WM_LBUTTONDOWN:
    xc = LOWORD(lp);
    yc = HIWORD(lp);
    break;
  case WM_LBUTTONUP:
    x = LOWORD(lp);
    y = HIWORD(lp);
    r = sqrt(pow(x - xc, 2) + pow(y - yc, 2));
    hdc = GetDC(hwnd);
    CircleBresenham(hdc, xc, yc, r, RGB(0, 255, 0));
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