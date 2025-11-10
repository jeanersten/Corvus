#pragma once

#include "../../source/Platform/Platform.hpp"

#if defined(CORVUS_PLATFORM_WIN32)
  #include <windows.h>

  // NOTE: SetDataPointer stuff probably overengineered.

  #if defined(CORVUS_DEBUG)
    #define CORVUS_REGISTER_APPLICATION_ENTRY(C)               \
    int wmain(int argc, wchar_t* argv[])                       \
    {                                                          \
      HANDLE stdout_handle{ GetStdHandle(STD_OUTPUT_HANDLE) }; \
      DWORD mode{ 0 };                                         \
                                                               \
      GetConsoleMode(stdout_handle, &mode);                    \
      mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;              \
      SetConsoleMode(stdout_handle, mode);                     \
                                                               \
      HINSTANCE instance{ GetModuleHandle(NULL) };             \
      PWSTR cmd_line{ GetCommandLine() };                      \
      int show_code{ SW_SHOWDEFAULT };                         \
                                                               \
      Corvus::Platform::SetDataPointer(1, &instance);          \
      Corvus::Platform::SetDataPointer(2, &cmd_line);          \
      Corvus::Platform::SetDataPointer(3, &show_code);         \
                                                               \
      C* app{ new C() };                                       \
      app->Run();                                              \
                                                               \
      delete app;                                              \
                                                               \
      return 0;                                                \
    }
  #else
    #define CORVUS_REGISTER_APPLICATION_ENTRY(C)       \
    int wWinMain(HINSTANCE instance, HINSTANCE,        \
                 PWSTR cmd_line, int show_code)        \
    {                                                  \
      Corvus::Platform::SetDataPointer(1, &instance);  \
      Corvus::Platform::SetDataPointer(2, &cmd_line);  \
      Corvus::Platform::SetDataPointer(3, &show_code); \
                                                       \
      C* app{ new C() };                               \
      app->Run();                                      \
                                                       \
      delete app;                                      \
                                                       \
      return 0;                                        \
    }
   #endif
#else
  #define CORVUS_REGISTER_APPLICATION_ENTRY(C)
  #error [Platform is not supported!]
#endif
