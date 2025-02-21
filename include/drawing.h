#ifndef DRAWING_H
#define DRAWING_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @brief Namespace for all drawing functions
 */
namespace Drawing
{
  /**
   * @brief Swaps two integers
   *
   * @param a first int
   * @param b second int
   */
  void swap(int &a, int &b);

  /**
   * @brief Rounds double to integer
   *
   * @param n number to round
   * @return rounded number
   */
  int round(double n);

  /**
   * @brief Represents the rgb values of a color
   *
   */
  struct COLORREF
  {
    float r, g, b;
    COLORREF(float red, float green, float blue) : r(red), g(green), b(blue) {}
  };

  /**
   * @brief Draw a pixel
   *
   * @param x     x coordinate of the first pixel
   * @param y     y coordinate of the first pixel
   * @param color rgb values of the color to use
   */
  void SetPixel(int x, int y, COLORREF color);

  /**
   * @brief Naive algorithm for drawing a line.
   *
   * @param x1    x coordinate of the first point
   * @param y1    y coordinate of the first point
   * @param x2    x coordinate of the second point
   * @param y2    y coordinate of the second point
   * @param color rgb values of the color to use
   */
  void DrawLine(int x1, int y1, int x2, int y2, COLORREF color);

  /**
   * @brief Improved naive algorithm for drawing a line.
   *
   * @details This implementation fixes the issue where the line
   * appears doted when the slope is bigger than one.
   *
   * @param x1    x coordinate of the first point
   * @param y1    y coordinate of the first point
   * @param x2    x coordinate of the second point
   * @param y2    y coordinate of the second point
   * @param color rgb values of the color to use
   */
  void DrawLine2(int x1, int y1, int x2, int y2, COLORREF color);

  /**
   * @brief Draw a line using simple digital differential
   * analyzer (DDA) method.
   *
   * @details This implementation is better than the naive one, because
   * it gets rid of float multiplication which makes it faster.
   *
   * @param x1    x coordinate of the first point
   * @param y1    y coordinate of the first point
   * @param x2    x coordinate of the second point
   * @param y2    y coordinate of the second point
   * @param color rgb values of the color to use
   */
  void SimpleDDA(int x1, int y1, int x2, int y2, COLORREF color);
} // namespace Drawing

#endif
