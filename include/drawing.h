#ifndef DRAWING_H
#define DRAWING_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// SetPixel function declaration
void SetPixel(int x, int y, float r, float g, float b);

// Line Drawing Algorithms
void DrawLine(int x1, int y1, int x2, int y2, float r, float g, float b);

#endif
