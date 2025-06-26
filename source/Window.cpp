#include "Log.h"
#include "Window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

cvs::Window::Window(int width, int height, const char* title)
  : m_width(width)
  , m_height(height)
  , m_title(title)
  , m_object(nullptr)
{}

cvs::Window::~Window()
{}

void cvs::Window::onResize(int width, int height)
{
  m_width = width;
  m_height = height;

  glViewport(0, 0, m_width, m_height);
}

void cvs::Window::glfw_framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
  Window* current_window = static_cast<Window*>(glfwGetWindowUserPointer(window));

  current_window->onResize(width, height);
}

void cvs::Window::create()
{
  m_object = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
  if (m_object == nullptr)
  {
    LOG_CRITICAL("Failed to create window instance!");
  }
  glfwMakeContextCurrent(m_object);
  glfwSwapInterval(1);
  glfwSetWindowUserPointer(m_object, this);
  glfwSetFramebufferSizeCallback(m_object, glfw_framebufferSizeCallback);

  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
  {
    LOG_CRITICAL("Failed to load OpenGL!");
  }
}

void cvs::Window::clear()
{
  glClearColor(0.4f, 0.5f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void cvs::Window::display()
{
  glfwSwapBuffers(m_object);
  glfwPollEvents();
}

bool cvs::Window::closed() const
{
  return glfwWindowShouldClose(m_object);
}

GLFWwindow* cvs::Window::getPointer() const
{
  return m_object;
}
