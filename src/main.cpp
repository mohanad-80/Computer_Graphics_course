#include <iostream>

#include "../include/drawing.h"

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
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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

  std::cout << glGetString(GL_VERSION) << '\n';

  // 🟢 Set up an orthographic projection to use (x, y) as pixel coordinates
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 640, 0, 480, -1, 1); // Match the window size (640x480)
  glMatrixMode(GL_MODELVIEW);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);

    for (size_t i = 100; i <= 200; i++)
    {
      SetPixel(i, i, 1.0f, 0.0f, 0.0f); // Red pixel
    }

    SetPixel(200, 150, 0.0f, 1.0f, 0.0f); // Green pixel at (200,150)
    SetPixel(300, 200, 0.0f, 0.0f, 1.0f); // Blue pixel at (300,200)

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}