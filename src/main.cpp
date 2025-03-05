#include <iostream>

#include "../include/drawing.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

int main(void)
{
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << '\n';
    return -1;
  }

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
  if (!window)
  {
    std::cout << "Failed to create GLFW window" << '\n';
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << '\n';
    return -1;
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;

  // 🟢 Set up an orthographic projection to use (x, y) as pixel coordinates
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1); // Match the window size
  glMatrixMode(GL_MODELVIEW);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    Drawing::COLORREF red(1.0f, 0.0f, 0.0f);
    Drawing::COLORREF green(0.0f, 1.0f, 0.0f);
    Drawing::COLORREF blue(0.0f, 0.0f, 1.0f);
    Drawing::COLORREF yellow(1.0f, 1.0f, 0.0f);

    // test SetPixel
    // for (size_t i = 100; i <= 200; i++)
    // {
    //   Drawing::SetPixel(i, i, {1.0f, 0.0f, 0.0f});
    // }

    // Drawing::TestLineDrawingFunction(Drawing::LineNaive);  // Naïve Algorithm
    // Drawing::TestLineDrawingFunction(Drawing::LineImprovedNaive); // Improved Algorithm
    // Drawing::TestLineDrawingFunction(Drawing::LineSimpleDDA); // LineSimpleDDA Algorithm
    // Drawing::TestLineDrawingFunction(Drawing::LineBresenham); // Bresenham Algorithm

    Drawing::CircleCartesian(100, 100, 50, green);
    Drawing::CirclePolar(250, 250, 50, red);
    Drawing::CircleIterativePolar(400, 100, 50, blue);
    Drawing::CircleBresenham(550, 250, 50, yellow);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}