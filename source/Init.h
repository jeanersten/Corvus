#pragma once

namespace cvs
{
  class Init
  {
  private:
    static void glfw_errorCallback(int error_code, const char* description);

  public:
    Init();
    ~Init();

    static void setup();
    static void cleanup();
  };
}
