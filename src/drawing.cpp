#include <cmath>

#include "drawing.h"

namespace Drawing
{
  void swap(int &a, int &b)
  {
    int temp = a;
    a = b;
    b = temp;
    return;
  }

  int round(double n)
  {
    return (int)(n + 0.5);
  }

  void SetPixel(int x, int y, COLORREF color)
  {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
  }

  void DrawLine(int x1, int y1, int x2, int y2, COLORREF color)
  {
    int dx = x2 - x1;
    int dy = y2 - y1;
    double m = (double)dy / dx;

    if (x1 > x2)
    {
      swap(x1, x2);
      swap(y1, y2);
    }

    for (int x = x1; x < x2; x++)
    {
      int y = round(m * (x - x1)) + y1;
      SetPixel(x, y, color);
    }
  }

  void DrawLine2(int x1, int y1, int x2, int y2, COLORREF color)
  {
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (std::abs(dy) <= std::abs(dx))
    {
      if (dx == 0)
      {
        SetPixel(x1, y1, color);
        return;
      }

      double m = (double)dy / dx;
      if (x1 > x2)
      {
        swap(x1, x2);
        swap(y1, y2);
      }

      for (int x = x1; x < x2; x++)
      {
        int y = round(m * (x - x1)) + y1;
        SetPixel(x, y, color);
      }
    }
    else
    {
      double mi = (double)dx / dy; // inverse of slope
      if (y1 > y2)
      {
        swap(x1, x2);
        swap(y1, y2);
      }

      for (int y = y1; y < y2; y++)
      {
        int x = round(mi * (y - y1)) + x1;
        SetPixel(x, y, color);
      }
    }
  }
} // namespace Drawing