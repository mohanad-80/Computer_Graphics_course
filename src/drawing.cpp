#include <iostream>
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

  void LineNaive(int x1, int y1, int x2, int y2, COLORREF color)
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

  void LineImprovedNaive(int x1, int y1, int x2, int y2, COLORREF color)
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

  void LineSimpleDDA(int x1, int y1, int x2, int y2, COLORREF color)
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

      int x = x1;
      double y = y1;
      while (x <= x2)
      {
        SetPixel(x, round(y), color);
        x++;
        y += m;
      }
    }
    else
    {
      double mi = (double)dx / dy;
      if (y1 > y2)
      {
        swap(x1, x2);
        swap(y1, y2);
      }

      double x = x1;
      int y = y1;
      while (y <= y2)
      {
        SetPixel(round(x), y, color);
        y++;
        x += mi;
      }
    }
  }

  void LineBresenham(int x1, int y1, int x2, int y2, COLORREF color)
  {
    bool steep = abs(y2 - y1) > abs(x2 - x1);

    // If the line is steep, swap x and y coordinates.
    // now x represent y and vice versa meaning that the
    // slope is inverted.
    if (steep)
    {
      std::swap(x1, y1);
      std::swap(x2, y2);
    }

    // Ensure left-to-right drawing
    if (x1 > x2)
    {
      std::swap(x1, x2);
      std::swap(y1, y2);
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
        SetPixel(y, x, color); // Swap back if steep
      else
        SetPixel(x, y, color);

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

  void TestLineDrawingFunction(std::function<void(int, int, int, int, COLORREF)> function)
  {
    function(200, 200, 350, 100, {0.0f, 1.0f, 0.0f}); // Case 1: Right & Up, Shallow (dx > 0, dy < 0, |m| < 1)
    function(200, 200, 220, 50, {0.0f, 1.0f, 0.0f});  // Case 2: Right & Up, Steep (dx > 0, dy < 0, |m| > 1)
    function(200, 200, 350, 300, {0.0f, 1.0f, 0.0f}); // Case 3: Right & Down, Shallow (dx > 0, dy > 0, |m| < 1)
    function(200, 200, 220, 400, {0.0f, 1.0f, 0.0f}); // Case 4: Right & Down, Steep (dx > 0, dy > 0, |m| > 1)
    function(200, 200, 50, 300, {0.0f, 1.0f, 0.0f});  // Case 5: Left & Down, Shallow (dx < 0, dy > 0, |m| < 1)
    function(200, 200, 180, 400, {0.0f, 1.0f, 0.0f}); // Case 6: Left & Down, Steep (dx < 0, dy > 1, |m| > 1)
    function(200, 200, 50, 100, {0.0f, 1.0f, 0.0f});  // Case 7: Left & Up, Shallow (dx < 0, dy < 0, |m| < 1)
    function(200, 200, 180, 50, {0.0f, 1.0f, 0.0f});  // Case 8: Left & Up, Steep (dx < 0, dy < 0, |m| > 1)
  }

  void draw8Points(int xc, int yc, int x, int y, COLORREF color)
  {
    SetPixel(xc + x, yc + y, color);
    SetPixel(xc - x, yc + y, color);
    SetPixel(xc + x, yc - y, color);
    SetPixel(xc - x, yc - y, color);
    SetPixel(xc + y, yc + x, color);
    SetPixel(xc - y, yc + x, color);
    SetPixel(xc + y, yc - x, color);
    SetPixel(xc - y, yc - x, color);
  }

  void CircleCartesian(int xc, int yc, int r, COLORREF color)
  {
    int x = 0, y = r;
    while (x <= y)
    {
      draw8Points(xc, yc, x, y, color);
      x++;
      y = round(sqrt(r * r - x * x));
    }
  }

  void CirclePolar(int xc, int yc, int r, COLORREF color)
  {
    int x = r, y = 0;
    double theta = 0, thetaStep = 1.0 / r;
    while (y <= x)
    {
      draw8Points(xc, yc, x, y, color);
      theta += thetaStep;
      x = round(r * cos(theta));
      y = round(r * sin(theta));
    }
  }

  void CircleIterativePolar(int xc, int yc, int r, COLORREF color)
  {
    double x = r, y = 0;
    double thetaStep = 1.0 / r;
    double cosTheta = cos(thetaStep), sinTheta = sin(thetaStep);
    while (y <= x)
    {
      draw8Points(xc, yc, x, y, color);
      double temp = x * cosTheta - y * sinTheta;
      y = x * sinTheta + y * cosTheta;
      x = temp;
    }
  }

  void CircleBresenham(int xc, int yc, int r, COLORREF color)
  {
    int x = 0, y = r;
    int d = 1 - r; // approximation
    int d1 = 3, d2 = 5 - 2 * r;
    draw8Points(xc, yc, x, y, color);
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

      draw8Points(xc, yc, x, y, color);
    }
  }

  void LineInterpolation(int x1, int y1, int x2, int y2, COLORREF color)
  {
    int alpha1 = x2 - x1, alpha2 = y2 - y1;
    double tStep = 1.0 / std::max(std::abs(alpha1), std::abs(alpha2));

    for (double t = 0; t <= 1; t += tStep)
    {
      double x = alpha1 * t + x1;
      double y = alpha2 * t + y1;
      SetPixel(round(x), round(y), color);
    }
  }

  void LineGradientInterpolation(int x1, int y1, int x2, int y2, COLORREF color1, COLORREF color2)
  {
    int alpha1 = x2 - x1, alpha2 = y2 - y1;
    float alpha3 = color2.r - color1.r;
    float alpha4 = color2.g - color1.g;
    float alpha5 = color2.b - color1.b;
    double tStep = 1.0 / std::max(std::abs(alpha1), std::abs(alpha2));

    for (double t = 0; t <= 1; t += tStep)
    {
      double x = alpha1 * t + x1;
      double y = alpha2 * t + y1;
      float r = alpha3 * t + color1.r;
      float g = alpha4 * t + color1.g;
      float b = alpha5 * t + color1.b;
      SetPixel(round(x), round(y), {r, g, b});
    }
  }
} // namespace Drawing