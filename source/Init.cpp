#include "Init.h"
#include "Log.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

cvs::Init::Init()
{}

cvs::Init::~Init()
{}

void cvs::Init::glfw_errorCallback(int error_code, const char* description)
{
  LOG_ERROR("(GLFW | {}) {}", error_code, description);
}

void cvs::Init::setup()
{
  Log::setup();
  Log::setLogLevel(LOG_LEVEL_TRACE);
  
  glfwSetErrorCallback(glfw_errorCallback);
  if (!glfwInit())
  {
    LOG_CRITICAL("Failed to initialize GLFW!");
  }
}

void cvs::Init::cleanup()
{
  glfwTerminate();
}
