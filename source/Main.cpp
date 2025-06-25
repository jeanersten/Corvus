#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

int main()
{
  spdlog::set_level(spdlog::level::trace);
  spdlog::trace("welcome to Corvus Engine!");

  if (glfwInit())
  {
    spdlog::info("GLFW initialized!");
  }

  GLFWwindow* window = glfwCreateWindow(640, 480, "Corvus", nullptr, nullptr);
  if (window != nullptr)
  {
    spdlog::info("GLFW window created!");
    glfwMakeContextCurrent(window);
  }

  if (gladLoadGL((GLADloadfunc)glfwGetProcAddress))
  {
    spdlog::info("GLAD loaded OpenGL");
  }

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  spdlog::info("Program terminated normally!");
  return 0;
}
