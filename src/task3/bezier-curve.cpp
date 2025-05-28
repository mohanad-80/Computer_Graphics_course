/**
 * @file bezier-curve.cpp
 *
 * * running command:
 * g++ ./bezier-curve.cpp -o bezier-curve -mwindows && ./bezier-curve.exe
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <Windows.h> 
#include <cmath>     
#include <cstdlib>   
#include <ctime>     
#include <array>     

using Matrix4x4 = std::array<std::array<double, 4>, 4>;
using Matrix4x2 = std::array<std::array<double, 2>, 4>;
using Vector4 = std::array<double, 4>;
using Vector2 = std::array<double, 2>;

int num_of_clicks = 0;
Matrix4x2 points;

// Function to generate a random color
COLORREF GetRandomColor()
{
  return RGB(rand() % 256, rand() % 256, rand() % 256); // Return a random color
}

// Multiply a 4x4 matrix by 4x2 matrix
Matrix4x2 multiply(const Matrix4x4 &a, const Matrix4x2 &b)
{
  Matrix4x2 result{};

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 2; ++j)
    {
      result[i][j] = 0.0;
      for (int k = 0; k < 4; ++k)
      {
        result[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  return result;
}

// Function to draw a color interpolated bezier curve
void CurveBezier(HDC hdc, Matrix4x2 pts, int numOfPts, COLORREF color)
{
  Matrix4x4 bezierMatrix = {{{-1, 3, -3, 1},
                             {3, -6, 3, 0},
                             {-3, 3, 0, 0},
                             {1, 0, 0, 0}}};

  Matrix4x2 geometryMatrix = pts;

  Matrix4x2 c = multiply(bezierMatrix, geometryMatrix);

  double tStep = 1.0 / numOfPts;

  for (double t = 0; t <= 1; t += tStep)
  {
    // x = alpha * t^3 + beta * t^2 + gama * t + delta
    double x = c[0][0] * t * t * t + c[1][0] * t * t + c[2][0] * t + c[3][0];
    double y = c[0][1] * t * t * t + c[1][1] * t * t + c[2][1] * t + c[3][1];
    SetPixel(hdc, round(x), round(y), color);
  }
}

// Window procedure function to handle messages
LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
  HDC hdc;   // Handle to device context
  RECT rect; // Rectangle structure

  switch (m)
  {
  case WM_LBUTTONDOWN: // Handle left mouse button down
    if (num_of_clicks <= 2)
    {
      points[num_of_clicks][0] = LOWORD(lp); // Get x coordinate of mouse click
      points[num_of_clicks][1] = HIWORD(lp); // Get y coordinate of mouse click
      num_of_clicks++;
    }
    else if (num_of_clicks == 3)
    {
      points[num_of_clicks][0] = LOWORD(lp); // Get x coordinate of mouse click
      points[num_of_clicks][1] = HIWORD(lp); // Get y coordinate of mouse click
      hdc = GetDC(hwnd);
      CurveBezier(hdc, points, 1000, GetRandomColor()); // Draw the bezier curve
      ReleaseDC(hwnd, hdc);
      num_of_clicks = 0;
    }
    break;
  case WM_RBUTTONDOWN:          // Handle right mouse button down
    hdc = GetDC(hwnd);          // Get device context for the window
    GetClientRect(hwnd, &rect); // Get the client area of the window

    // Clear the window to black
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    ReleaseDC(hwnd, hdc); // Release device context
    break;
  case WM_CLOSE:         // Handle window close
    DestroyWindow(hwnd); // Destroy the window
    break;
  case WM_DESTROY:      // Handle window destroy
    PostQuitMessage(0); // Post a quit message
    break;
  default:
    return DefWindowProc(hwnd, m, wp, lp); // Default window procedure
  }
  return 0;
}

// Entry point for the application
int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR cmd, int nsh)
{
  srand(time(0));    // Seed the random number generator
  WNDCLASSW wc;      // Declare a window class structure
  wc.cbClsExtra = 0; // No extra class memory
  wc.cbWndExtra = 0; // No extra window memory
  // Set background brush to black
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Load the arrow cursor
  wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);   // Load the default icon
  wc.lpszClassName = L"MyClass";            // Set the class name
  wc.lpszMenuName = NULL;                   // No menu
  wc.lpfnWndProc = WndProc;                 // Set the window procedure
  wc.style = CS_HREDRAW | CS_VREDRAW;       // Set the class style
  wc.hInstance = hi;                        // Set the instance handle
  RegisterClassW(&wc);                      // Register the window class

  // Create the window
  HWND hwnd = CreateWindowW(L"MyClass", L"Hello World!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hi, 0);
  ShowWindow(hwnd, nsh); // Show the window
  UpdateWindow(hwnd);    // Update the window

  MSG msg; // Declare a message structure
  // Message loop
  while (GetMessage(&msg, NULL, 0, 0) > 0)
  {
    TranslateMessage(&msg); // Translate the message
    DispatchMessage(&msg);  // Dispatch the message
  }
  return 0; // Return the exit code
}