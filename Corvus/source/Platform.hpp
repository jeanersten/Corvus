#pragma once

#include "Core/Core.hpp"

#ifdef CORVUS_PLATFORM_WIN32
  #include <windows.h>

  int wWinMain(HINSTANCE, HINSTANCE, PWSTR, int);
  int wmain(int, wchar_t**);
#endif

namespace Corvus
{
  class CORVUS_API Platform
  {
    #ifdef CORVUS_PLATFORM_WIN32
      friend int ::wWinMain(HINSTANCE, HINSTANCE, PWSTR, int);
      friend int ::wmain(int, wchar_t**);
    #endif

  public:
    template<typename T>
    static const T* GetDataPointer(int index)
    {
      return reinterpret_cast<const T*>(s_platform_data[index]);
    }

  private:
    Platform() = delete;
    ~Platform() = delete;

    static constexpr int MAX_PLATFORM_DATA { 15 };

    static const void* s_platform_data[];
  };
}
