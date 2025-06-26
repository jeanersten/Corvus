#pragma once

#include <GLFW/glfw3.h>

namespace cvs
{
  class Window
  {
  private:
    int m_width;
    int m_height;
    const char* m_title;

    GLFWwindow* m_object;

    void onResize(int width, int height);
    static void glfw_framebufferSizeCallback(GLFWwindow* window, int width, int height);

  public:
    Window(int width, int height, const char* title);
    ~Window();

    void create();
    void clear();
    void display();
    bool closed() const;
    GLFWwindow* getPointer() const;
  };
}
