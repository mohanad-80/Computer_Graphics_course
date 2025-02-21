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

    // Slope < 1 (shallow)
    Drawing::DrawLine(150, 100, 250, 150, red);  // Naïve Algorithm
    Drawing::DrawLine2(160, 100, 260, 150, red); // Improved Algorithm
    Drawing::SimpleDDA(170, 100, 270, 150, red); // SimpleDDA Algorithm

    // Slope > 1 (steep)
    Drawing::DrawLine(100, 50, 150, 250, blue);  // Naïve Algorithm
    Drawing::DrawLine2(110, 50, 160, 250, blue); // Improved Algorithm
    Drawing::SimpleDDA(120, 50, 170, 250, blue); // SimpleDDA Algorithm

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}