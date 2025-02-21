#include "drawing.h"

namespace Drawing
{
  // Function to draw a single pixel
  void SetPixel(int x, int y, COLORREF color)
  {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
  }
} // namespace Drawing