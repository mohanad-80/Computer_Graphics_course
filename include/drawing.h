#ifndef DRAWING_H
#define DRAWING_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <array>

using Matrix4x4 = std::array<std::array<double, 4>, 4>;
using Matrix4x2 = std::array<std::array<double, 2>, 4>;
using Vector4 = std::array<double, 4>;
using Vector2 = std::array<double, 2>;

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

  Matrix4x2 multiply(const Matrix4x4 &a, const Matrix4x2 &b);
  Vector4 multiply(const Matrix4x4 &mat, const Vector4 &vec);
  Vector2 multiply(const Matrix4x2 &mat, const Vector4 &vec);

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
  void LineNaive(int x1, int y1, int x2, int y2, COLORREF color);

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
  void LineImprovedNaive(int x1, int y1, int x2, int y2, COLORREF color);

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
  void LineSimpleDDA(int x1, int y1, int x2, int y2, COLORREF color);

  /**
   * @brief Draw a line using Bresenham (midpoint) algorithm.
   *
   * @details This implementation gets rid of any floating point
   * operations and only works with integers which improves the
   * algorithm's performance greatly.
   *
   * @param x1    x coordinate of the first point
   * @param y1    y coordinate of the first point
   * @param x2    x coordinate of the second point
   * @param y2    y coordinate of the second point
   * @param color rgb values of the color to use
   */
  void LineBresenham(int x1, int y1, int x2, int y2, COLORREF color);

  /**
   * @brief Tests one of the functions for drawing a line by drawing
   * all possible cases.
   *
   * @details Cases tested:
   * Case 1: Right & Up, Shallow (dx > 0, dy < 0, |m| < 1)
   * Case 2: Right & Up, Steep (dx > 0, dy < 0, |m| > 1)
   * Case 3: Right & Down, Shallow (dx > 0, dy > 0, |m| < 1)
   * Case 4: Right & Down, Steep (dx > 0, dy > 0, |m| > 1)
   * Case 5: Left & Down, Shallow (dx < 0, dy > 0, |m| < 1)
   * Case 6: Left & Down, Steep (dx < 0, dy > 1, |m| > 1)
   * Case 7: Left & Up, Shallow (dx < 0, dy < 0, |m| < 1)
   * Case 8: Left & Up, Steep (dx < 0, dy < 0, |m| > 1)
   *
   * @param function The functions to be tested.
   */
  void TestLineDrawingFunction(std::function<void(int, int, int, int, COLORREF)> function);

  // ===================================
  // Circle functions ==================
  // ===================================

  /**
   * @brief Utility function used by circle functions that draws
   * eight points.
   *
   * @details It makes use of the circle similarity property.
   *
   * @param xc    x coordinate of the circle's center
   * @param yc    y coordinate of the circle's center
   * @param x     the x distance from the circle's center
   * @param y     the y distance from the circle's center
   * @param color rgb values of the color to use
   */
  void draw8Points(int xc, int yc, int x, int y, COLORREF color);

  /**
   * @brief Draw a circle using a naive cartesian algorithm.
   *
   * @param xc    x coordinate of the circle's center
   * @param yc    y coordinate of the circle's center
   * @param r     the radius of the circle
   * @param color rgb values of the color to use
   */
  void CircleCartesian(int xc, int yc, int r, COLORREF color);

  /**
   * @brief Draw a circle using a naive polar algorithm.
   *
   * @param xc    x coordinate of the circle's center
   * @param yc    y coordinate of the circle's center
   * @param r     the radius of the circle
   * @param color rgb values of the color to use
   */
  void CirclePolar(int xc, int yc, int r, COLORREF color);

  /**
   * @brief Draw a circle using a iterative polar algorithm.
   *
   * @details This algorithm only calculate the cos and sin only
   * once which makes it faster than the normal polar algorithm
   *
   * @param xc    x coordinate of the circle's center
   * @param yc    y coordinate of the circle's center
   * @param r     the radius of the circle
   * @param color rgb values of the color to use
   */
  void CircleIterativePolar(int xc, int yc, int r, COLORREF color);

  /**
   * @brief Draw a circle using a Bresenham's (midpoint) algorithm.
   *
   * @details This algorithm uses only integer operation which
   * is faster than the other algorithms.
   *
   * @param xc    x coordinate of the circle's center
   * @param yc    y coordinate of the circle's center
   * @param r     the radius of the circle
   * @param color rgb values of the color to use
   */
  void CircleBresenham(int xc, int yc, int r, COLORREF color);

  // ===================================
  // Curves functions ==================
  // ===================================

  /**
   * @brief Draw a line using Interpolation algorithm.
   *
   * @param x1    x coordinate of the first point
   * @param y1    y coordinate of the first point
   * @param x2    x coordinate of the second point
   * @param y2    y coordinate of the second point
   * @param color rgb values of the color to use
   */
  void LineInterpolation(int x1, int y1, int x2, int y2, COLORREF color);

  /**
   * @brief Draw a line with color gradient using Interpolation algorithm.
   *
   * @param x1    x coordinate of the first point
   * @param y1    y coordinate of the first point
   * @param x2    x coordinate of the second point
   * @param y2    y coordinate of the second point
   * @param color rgb values of the color to use
   */
  void LineGradientInterpolation(int x1, int y1, int x2, int y2, COLORREF color1, COLORREF color2);

  /**
   * @brief draw a curve using Interpolation algorithm.
   *
   * @param x1       x coordinate of the first point
   * @param y1       y coordinate of the first point
   * @param x2       x coordinate of the second point
   * @param y2       y coordinate of the second point
   * @param x3       x coordinate of the third point
   * @param y3       y coordinate of the third point
   * @param numOfPts number of points to draw on the curve
   * @param color    rgb values of the color to use
   */
  void CurveInterpolation(int x1, int y1, int x2, int y2, int x3, int y3, int numOfPts, COLORREF color);
  
  void CurveHermite(int x1, int y1, int u1, int v1, int x2, int y2, int u2, int v2, int numOfPts, COLORREF color);

  void CurveBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int numOfPts, COLORREF color);
} // namespace Drawing

#endif
