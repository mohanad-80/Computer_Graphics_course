#include <Windows.h> // Include Windows API
#include <cmath>     // Include math functions
#include <cstdlib>   // Include standard library functions for random number generation
#include <ctime>     // Include time functions

int xs, ys, xe, ye; // Declare global variables for start and end coordinates

// Function to generate a random color
COLORREF GetRandomColor()
{
  return RGB(rand() % 256, rand() % 256, rand() % 256); // Return a random color
}

// Function to draw an interpolated colored line
void InterpolatedColoredLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c1, COLORREF c2)
{
  int alpha1 = x2 - x1, alpha2 = y2 - y1; // Calculate differences in x and y coordinates

  int alpha3 = GetRValue(c2) - GetRValue(c1); // Calculate difference in red component
  int alpha4 = GetGValue(c2) - GetGValue(c1); // Calculate difference in green component
  int alpha5 = GetBValue(c2) - GetBValue(c1); // Calculate difference in blue component

  // Calculate step size for interpolation
  double tStep = 1.0 / std::max(std::abs(alpha1), std::abs(alpha2));

  // Loop to draw the line with interpolated colors
  for (double t = 0; t <= 1; t += tStep)
  {
    double x = alpha1 * t + x1; // Interpolate x coordinate
    double y = alpha2 * t + y1; // Interpolate y coordinate

    int r = round(alpha3 * t + GetRValue(c1)); // Interpolate red component
    int g = round(alpha4 * t + GetGValue(c1)); // Interpolate green component
    int b = round(alpha5 * t + GetBValue(c1)); // Interpolate blue component

    SetPixel(hdc, round(x), round(y), RGB(r, g, b)); // Set the pixel with interpolated color
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
    xs = LOWORD(lp);   // Get x coordinate of mouse click
    ys = HIWORD(lp);   // Get y coordinate of mouse click
    break;
  case WM_LBUTTONUP: // Handle left mouse button up
    xe = LOWORD(lp); // Get x coordinate of mouse release
    ye = HIWORD(lp); // Get y coordinate of mouse release

    hdc = GetDC(hwnd); // Get device context for the window
    // Draw interpolated colored line
    InterpolatedColoredLine(hdc, xs, ys, xe, ye, GetRandomColor(), GetRandomColor());
    ReleaseDC(hwnd, hdc); // Release device context
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