#pragma once

#include "../../source/Application.hpp"
#include "../../source/Event.hpp"
#include "../../source/Log.hpp"
#include "../../source/Platform.hpp"
#include "../../source/Window.hpp"

#if defined(CORVUS_PLATFORM_WIN32)
  #include <windows.h>

  // entry point
  #if defined(CORVUS_DEBUG)
    #define CORVUS_REGISTER_APPLICATION_ENTRY(C)         \
    int wmain(int argc, wchar_t* argv[])                 \
    {                                                    \
      HINSTANCE instance { GetModuleHandle(NULL) };      \
      PWSTR cmd_line { GetCommandLine() };               \
      int show_code { SW_SHOWDEFAULT };                  \
                                                         \
      Corvus::Platform::s_platform_data[1] = &instance;  \
      Corvus::Platform::s_platform_data[2] = &cmd_line;  \
      Corvus::Platform::s_platform_data[3] = &show_code; \
                                                         \
      C* app { new C() };                                \
      app->Run();                                        \
                                                         \
      delete app;                                        \
                                                         \
      return 0;                                          \
    }
  #elif defined(CORVUS_RELEASE)
    #define CORVUS_REGISTER_APPLICATION_ENTRY(C)         \
    int wWinMain(HINSTANCE instance, HINSTANCE,          \
                 PWSTR cmd_line, int show_code)          \
    {                                                    \
      Corvus::Platform::s_platform_data[1] = &instance;  \
      Corvus::Platform::s_platform_data[2] = &cmd_line;  \
      Corvus::Platform::s_platform_data[3] = &show_code; \
                                                         \
      C* app { new C() };                                \
      app->Run();                                        \
                                                         \
      delete app;                                        \
                                                         \
      return 0;                                          \
    }
  #else
    #define CORVUS_REGISTER_APPLICATION_ENTRY(C)
  #endif
#else
  #define CORVUS_REGISTER_APPLICATION_ENTRY(C)
  #error [Platform is not supported!]
#endif
